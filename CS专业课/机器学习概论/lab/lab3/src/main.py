import numpy as np
import matplotlib.pyplot as plt
from xgboost import XGBoost


if __name__ == '__main__':
    x_train = np.load('./data/train_data.npy')
    y_train = np.load('./data/train_target.npy')
    x_test = np.load('./data/test_data.npy')
    y_test = np.load('./data/test_target.npy')

    # split_threshold = [5]
    split_threshold = [5, 2, 1]
    xgb = XGBoost(x_train, y_train, num_trees=len(split_threshold), lamb=1,
                  split_threshold_by_GH=True, split_threshold=split_threshold,
                  gamma=1)
    xgb.train()
    y_train_pred = xgb.predict(x_train, y_train)
    # print(np.unique(y_train_pred[1]))
    print(f'train acc: {y_train_pred[2]}')
    y_test_pred = xgb.predict(x_test, y_test)
    # print(np.unique(y_test_pred[1]))
    print(f'test acc: {y_test_pred[2]}')

    fig = plt.figure(figsize=(12, 9))
    subplot_size = [int(np.ceil(len(xgb.forest) / (int(np.sqrt(len(xgb.forest))) + 1))),
                    int(np.sqrt(len(xgb.forest))) + 1]
    for tree_idx, tree in enumerate(xgb.forest):
        ax = fig.add_subplot(*subplot_size, tree_idx+1)
        plt.title(f'tree {tree_idx}')
        tree.draw_tree()
    plt.tight_layout()
    plt.show()
