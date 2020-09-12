from infer_node import *
import time


def main():
    target = Formula.from_str(input('Please input the target formula: '))
    premise_set = []
    while True:
        premise = input('Please input the premise set one by one(enter to ignore): ')
        if not premise:
            break
        premise_set.append(Formula.from_str(premise, state=FormulaState.known))

    premise_strs = [str(i) for i in premise_set]
    print('Your target is: {}'.format(target))
    print('Your given premise set: {{{}}}'.format(', '.join(premise_strs)))

    if not target.get_truth_value_with_premise(premise_set):
        print("The Truth Value isn't True!")
        return

    print('Computing Begins!')
    begin = time.time()

    final_infer_node = InferNode.infer([InferNode(target, premise_set)])
    final_infer_node.print_process()

    end = time.time()
    print('\nTime Spent: {} s'.format(end - begin))


if __name__ == '__main__':
    main()
