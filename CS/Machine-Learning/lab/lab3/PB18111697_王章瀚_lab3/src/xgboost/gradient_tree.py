import numpy as np
import networkx as nx
import os.path as osp
from collections import namedtuple
from networkx.drawing.nx_agraph import graphviz_layout
import matplotlib.pyplot as plt

Criterion = namedtuple('Criterion', ('idx', 'threshold'))


class GradientTreeNode:
    def __init__(self, x_train, y_train, y_last_pred, lamb=1,
                 split_threshold_by_GH=False, split_threshold=0.1):
        assert len(x_train.shape) == 2
        assert len(y_train.shape) == 1
        assert x_train.shape[0] == y_train.shape[0]
        self.x_train = x_train
        self.y_train = y_train
        self.lamb = 1
        self.split_threshold_by_GH = split_threshold_by_GH
        self.split_threshold = split_threshold
        self.y_last_pred = y_last_pred
        self.g = self.g_func(self.y_train, self.y_last_pred)
        self.h = self.h_func(self.y_train, self.y_last_pred)
        self.G = self.g.sum()
        self.H = self.h.sum()
        if split_threshold_by_GH:
            self.split_threshold = np.sqrt(self.G**2 / (self.H + self.lamb))
        self.weight = -self.G / (self.H + self.lamb)
        self.left = None
        self.right = None
        self.criterion = Criterion('?', '?')

    def __repr__(self):
        if self.left is None and self.right is None:
            return f'{self.weight:.2f}'
        else:
            return f'x{self.criterion.idx}<{self.criterion.threshold: .2f}?'

    @property
    def feature_dim(self):
        return self.x_train.shape[1]

    @property
    def m(self):
        return self.x_train.shape[0]

    # gradient statistics
    @staticmethod
    def g_func(y_train, y_last_pred):
        return y_last_pred - y_train

    @staticmethod
    def h_func(y_train, y_last_pred):
        return np.ones(y_train.shape)

    def split(self):
        # datas
        x_train = self.x_train
        g, h = self.g, self.h
        G, H = self.G, self.H
        lamb = self.lamb
        # test if all instances are in the same class
        unique_y = np.unique(self.y_train)
        if unique_y.shape[0] == 1:
            return [self]
        # otherwise, find the best feature to split the node
        split = [0, 0]
        best_score = -np.inf
        gains = np.zeros((x_train.shape[-1::-1]))
        for k in range(self.feature_dim):
            G_L = 0
            H_L = 0
            args = np.argsort(x_train[:, k], axis=0)
            for i in range(len(args)):
                G_L += g[args[i]]
                H_L += h[args[i]]
                G_R = G - G_L
                H_R = H - H_L
                gain = G_L ** 2 / (H_L + lamb) + G_R ** 2 / (H_R + lamb) - G ** 2 / (H + lamb)
                gains[k][i] = gain
                if gain > best_score:
                    best_score = gain
                    split = [k, i]
        # test if best_score is less than the thershold
        if best_score < self.split_threshold:
            return [self]
        # otherwise, we can split this node
        args = np.argsort(x_train[:, split[0]], axis=0)
        self.criterion = Criterion(split[0], x_train[args[split[1]], split[0]])
        left_idx = args[:split[1] + 1]
        right_idx = args[split[1] + 1:]
        assert len(left_idx) > 0 and len(right_idx) > 0
        self.left = GradientTreeNode(self.x_train[left_idx], self.y_train[left_idx], self.y_last_pred[left_idx],
                                     self.lamb,
                                     split_threshold_by_GH=self.split_threshold_by_GH,
                                     split_threshold=self.split_threshold)
        self.right = GradientTreeNode(self.x_train[right_idx], self.y_train[right_idx], self.y_last_pred[right_idx],
                                      self.lamb,
                                      split_threshold_by_GH=self.split_threshold_by_GH,
                                      split_threshold=self.split_threshold)
        return self.left.split() + self.right.split()

    def predict(self, x):
        assert len(x.shape) == 1 and x.shape[0] == self.feature_dim
        criterion = self.criterion
        if self.left is None or self.right is None:
            return self.weight
        if x[criterion.idx] < criterion.threshold:
            return self.left.predict(x)
        else:
            return self.right.predict(x)


class GradientTree:
    def __init__(self, x_train, y_train, y_last_pred, lamb=1,
                 split_threshold_by_GH=False, split_threshold=0.01, gamma=1):
        self.x_train = x_train
        self.y_train = y_train
        self.y_last_pred = y_last_pred
        self.lamb = lamb
        self.split_threshold = split_threshold
        self.root = GradientTreeNode(x_train, y_train, y_last_pred, lamb=lamb,
                                     split_threshold_by_GH=split_threshold_by_GH,
                                     split_threshold=split_threshold)
        self.leaves = []
        self.graph = None
        self.gamma = gamma

    @property
    def obj(self):
        Gs = np.array([leaf.G for leaf in self.leaves])
        Hs = np.array([leaf.H for leaf in self.leaves])
        obj = -np.sum((Gs ** 2 / (Hs + self.lamb))) / 2 + self.gamma * len(self.leaves)
        return obj

    def train(self):
        self.leaves = self.root.split()

    def predict(self, x_test, y_test):
        correct_count = 0
        y_test_pred = []
        y_test_pred_prob = []
        for x, y in zip(x_test, y_test):
            y_pred_prob = self.root.predict(x)
            y_pred = 1 if y_pred_prob >= 0.5 else 0
            y_test_pred.append(y_pred)
            y_test_pred_prob.append(y_pred_prob)
            if y_pred == y:
                correct_count += 1
        acc = correct_count / len(y_test)
        y_test_pred = np.array(y_test_pred)
        y_test_pred_prob = np.array(y_test_pred_prob)
        return y_test_pred, y_test_pred_prob, acc

    def generate_graph(self):
        graph = nx.DiGraph()
        queue = [self.root]
        graph.add_nodes_from([(id(self.root), {'criterion': str(self.root)})])
        while len(queue) > 0:
            top = queue[0]
            queue = queue[1:]
            if top.left is None or top.right is None:
                assert top.left is None and top.right is None
                continue
            graph.add_nodes_from([(id(top.left), {'criterion': str(top.left)}),
                                  (id(top.right), {'criterion': str(top.right)})])
            graph.add_edges_from([(id(top), id(top.left)), (id(top), id(top.right))])
            queue.append(top.left)
            queue.append(top.right)
        self.graph = graph
        return graph

    def draw_tree(self):
        graph = self.generate_graph()
        labels = {}
        for node in graph.nodes.data():
            labels[node[0]] = node[1]['criterion']
        pos = graphviz_layout(graph, prog='dot')
        nx.draw(graph, pos=pos, with_labels=True, labels=labels)


if __name__ == '__main__':
    x_train = np.load(osp.join(osp.dirname(__file__), '../data/train_data.npy'))
    y_train = np.load(osp.join(osp.dirname(__file__), '../data/train_target.npy'))
    x_test = np.load(osp.join(osp.dirname(__file__), '../data/test_data.npy'))
    y_test = np.load(osp.join(osp.dirname(__file__), '../data/test_target.npy'))

    gt = GradientTree(x_train, y_train, np.zeros(y_train.shape), lamb=1, split_threshold=2)
    gt.train()
    print(np.unique(gt.predict(x_test, y_test)[1]))
    print(np.unique(gt.predict(x_test, y_test)[2]))
    gt.draw_tree()
    plt.show()
