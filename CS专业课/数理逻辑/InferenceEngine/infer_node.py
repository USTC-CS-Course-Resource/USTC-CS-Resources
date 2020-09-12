from formula import *
from copy import copy
import pandas as pd


class InferNode:
    MAX_IMP_NUM = 8
    MAX_LAYER_NUM = 6
    ENABLE_NUM = False
    ENABLE_L2_222 = False

    def __init__(self, root_f=None, premise_list=None):
        if premise_list is None:
            premise_list = []
        self.root_f = root_f
        self.premise_list = premise_list

    def get_leaves(self, need_done=False):
        leaves = []

        def get_leaves_sub(f: Formula):
            if f is None:
                return None
            get_leaves_sub(f.first)
            get_leaves_sub(f.whole)
            if f.first is None and f.whole is None:
                if need_done or f.state == FormulaState.todo:
                    leaves.append(f)

        get_leaves_sub(self.root_f)
        return leaves

    def copy(self, need_done=True):
        leaves = []

        def copy_sub(f: Formula):
            if f is None:
                return None
            new_f = copy(f)
            new_f.first = copy_sub(f.first)
            new_f.whole = copy_sub(f.whole)
            if new_f.first is None and new_f.whole is None:
                if need_done or new_f.state == FormulaState.todo:
                    leaves.append(new_f)
            return new_f

        return InferNode(copy_sub(self.root_f), premise_list=self.premise_list), leaves

    def copy_and_replace(self, replace_dict: dict, need_done=True):
        leaves = []

        def copy_sub(f: Formula):
            if f is None:
                return None
            new_f = copy(f)
            new_f.replace(replace_dict, inplace=True)
            new_f.first = copy_sub(f.first)
            new_f.whole = copy_sub(f.whole)
            if new_f.first is None and new_f.whole is None:
                if need_done or new_f.state == FormulaState.todo:
                    leaves.append(new_f)
            return new_f

        return InferNode(copy_sub(self.root_f), premise_list=self.premise_list), leaves

    def replace(self, replace_dict: dict):

        def replace_sub(f: Formula):
            if f is None:
                return None
            f.replace(replace_dict, inplace=True)
            replace_sub(f.first)
            replace_sub(f.whole)

        replace_sub(self.root_f)

    def infer_next(self):
        # 首先过一遍叶子结点看是否有可能判定为公理或者前提集公式
        leaves = self.get_leaves()
        leaves_num = len(leaves)
        new_infer_node_list = []
        for i in range(leaves_num):
            new_infer_node, leaves = self.copy()
            # 匹配L1模式
            result, exp_replace_dict, pattern_replace_dict = \
                leaves[i].try_fit(Formula.create_l1_pattern(), inplace=True)
            if result:
                if len(exp_replace_dict) != 0:
                    new_infer_node.replace(exp_replace_dict)
                if len(pattern_replace_dict) != 0:
                    new_infer_node.replace(pattern_replace_dict)
                if InferNode.ENABLE_NUM or \
                        leaves[i].imp_and_layer_num <= (InferNode.MAX_IMP_NUM, InferNode.MAX_LAYER_NUM):
                    new_infer_node_list += [new_infer_node]
                new_infer_node, leaves = self.copy()
            # 匹配L2模式
            result, exp_replace_dict, pattern_replace_dict = \
                leaves[i].try_fit(Formula.create_l2_pattern(), inplace=True)
            if result:
                if len(exp_replace_dict) != 0:
                    new_infer_node.replace(exp_replace_dict)
                if len(pattern_replace_dict) != 0:
                    new_infer_node.replace(pattern_replace_dict)
                if InferNode.ENABLE_NUM or \
                        leaves[i].imp_and_layer_num <= (InferNode.MAX_IMP_NUM, InferNode.MAX_LAYER_NUM):
                    new_infer_node_list += [new_infer_node]
                new_infer_node, leaves = self.copy()
            # 匹配L3模式
            result, exp_replace_dict, pattern_replace_dict = \
                leaves[i].try_fit(Formula.create_l3_pattern(), inplace=True)
            if result:
                if len(exp_replace_dict) != 0:
                    new_infer_node.replace(exp_replace_dict)
                if len(pattern_replace_dict) != 0:
                    new_infer_node.replace(pattern_replace_dict)
                if InferNode.ENABLE_NUM or \
                        leaves[i].imp_and_layer_num <= (InferNode.MAX_IMP_NUM, InferNode.MAX_LAYER_NUM):
                    new_infer_node_list += [new_infer_node]
                new_infer_node, leaves = self.copy()
            # 匹配前提集
            for premise in self.premise_list:
                result, exp_replace_dict, pattern_replace_dict = \
                    leaves[i].try_fit(premise, precise=True, inplace=True)
                if result:
                    if len(exp_replace_dict) != 0:
                        new_infer_node.replace(exp_replace_dict)
                    if InferNode.ENABLE_NUM or \
                            leaves[i].imp_and_layer_num <= (InferNode.MAX_IMP_NUM, InferNode.MAX_LAYER_NUM):
                        new_infer_node_list += [new_infer_node]
                    new_infer_node, leaves = self.copy()
            # 借由MP作推理
            #   L1的后件
            result, exp_replace_dict, pattern_replace_dict = leaves[i].try_as_l1_2()
            if result:
                if len(exp_replace_dict) != 0:
                    new_infer_node.replace(exp_replace_dict)
                if InferNode.ENABLE_NUM or \
                        leaves[i].imp_and_layer_num <= (InferNode.MAX_IMP_NUM, InferNode.MAX_LAYER_NUM):
                    new_infer_node_list.append(new_infer_node)
                new_infer_node, leaves = self.copy()
            #   L2的后件
            result, exp_replace_dict, pattern_replace_dict = leaves[i].try_as_l2_2()
            if result:
                if len(exp_replace_dict) != 0:
                    new_infer_node.replace(exp_replace_dict)
                if InferNode.ENABLE_NUM or \
                        leaves[i].imp_and_layer_num <= (InferNode.MAX_IMP_NUM, InferNode.MAX_LAYER_NUM):
                    new_infer_node_list.append(new_infer_node)
                new_infer_node, leaves = self.copy()
            #   L2的后件的后件
            if leaves[i].try_as_l2_22():
                if InferNode.ENABLE_NUM or \
                        leaves[i].imp_and_layer_num <= (InferNode.MAX_IMP_NUM, InferNode.MAX_LAYER_NUM):
                    new_infer_node_list.append(new_infer_node)
                new_infer_node, leaves = self.copy()
            #   L2的后件的后件的后件
            if InferNode.ENABLE_L2_222 and leaves[i].try_as_l2_222():
                if InferNode.ENABLE_NUM or \
                        leaves[i].imp_and_layer_num <= (InferNode.MAX_IMP_NUM, InferNode.MAX_LAYER_NUM):
                    new_infer_node_list.append(new_infer_node)
                new_infer_node, leaves = self.copy()
            #   L3的后件的后件
            if leaves[i].try_as_l3_2():
                if InferNode.ENABLE_NUM or \
                        leaves[i].imp_and_layer_num <= (InferNode.MAX_IMP_NUM, InferNode.MAX_LAYER_NUM):
                    new_infer_node_list.append(new_infer_node)
                new_infer_node, leaves = self.copy()
            #   L3的后件的后件
            if leaves[i].try_as_l3_22():
                if InferNode.ENABLE_NUM or \
                        leaves[i].imp_and_layer_num <= (InferNode.MAX_IMP_NUM, InferNode.MAX_LAYER_NUM):
                    new_infer_node_list.append(new_infer_node)

        return new_infer_node_list

    def print_process(self):
        f_count = 1

        def print_process_sub(root: Formula):
            nonlocal f_count
            if root.first is not None:
                print_process_sub(root.first)
            if root.whole is not None:
                print_process_sub(root.whole)
            root.index = f_count
            f_count += 1
            print(root.process_str())

        print_process_sub(self.root_f)

    def process_to_dataframe(self):
        f_count = 1
        process = []

        def set_process_sub(root: Formula):
            nonlocal f_count
            if root.first is not None:
                set_process_sub(root.first)
            if root.whole is not None:
                set_process_sub(root.whole)
            root.index = f_count
            f_count += 1
            process.append(('{}°'.format(root.index), str(root), root.come_from))

        set_process_sub(self.root_f)
        return pd.DataFrame(process, columns=['index', 'formula', 'come_from'])

    def __str__(self):
        leaf_strs = []
        for leaf in self.get_leaves():
            leaf_strs.append('{{{}, {}}}'.format(str(leaf), leaf.state.name))
        return '[' + ', '.join(leaf_strs) + ']'

    @staticmethod
    def infer(infer_node_queue):
        times = 1
        while True:
            q_size = len(infer_node_queue)
            times += 1
            if times % 100000 == 0:
                print('第{}次迭代, 队列长为{}'.format(times, q_size))
            if q_size == 0:
                return None
            for i in range(q_size):
                # pop
                infer_node = infer_node_queue[0]
                infer_node_queue = infer_node_queue[1:]
                next_infer_nodes = infer_node.infer_next()
                for new_infer_node in next_infer_nodes:
                    if not new_infer_node.get_leaves():
                        return new_infer_node
                else:
                    infer_node_queue += next_infer_nodes
