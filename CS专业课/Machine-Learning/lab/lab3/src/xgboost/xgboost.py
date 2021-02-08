import numpy as np
from typing import Union, List
from xgboost.gradient_tree import GradientTree


class XGBoost:
    def __init__(self, x_train, y_train,
                 num_trees=10, lamb=1,
                 split_threshold_by_GH=False, split_threshold: Union[int, List, np.ndarray] = 1,
                 gamma=1):
        self.x_train = x_train
        self.y_train = y_train
        self.forest = []
        self.num_trees = num_trees
        self.lamb = lamb
        self.split_threshold_by_GH = split_threshold_by_GH
        self.split_threshold = split_threshold
        self.gamma = gamma

    def train(self):
        x_train = self.x_train
        y_train = self.y_train
        y_last_pred = np.zeros(y_train.shape)
        split_threshold = self.split_threshold
        if type(split_threshold) == int:
            np.repeat(split_threshold, self.num_trees)
        else:
            assert len(split_threshold) == self.num_trees

        for tree_idx in range(self.num_trees):
            gt = GradientTree(x_train, y_train, y_last_pred,
                              lamb=self.lamb,
                              split_threshold_by_GH=self.split_threshold_by_GH,
                              split_threshold=split_threshold[tree_idx], gamma=self.gamma)
            gt.train()
            self.forest.append(gt)
            print((y_last_pred - y_train).mean(), gt.root.G**2 / (gt.root.H+self.lamb))
            y_last_pred += gt.predict(x_train, y_train)[1]

    def predict(self, x_test, y_test):
        y_test_pred_prob = np.zeros(y_test.shape)
        for gt in self.forest:
            y_test_pred_prob += gt.predict(x_test, y_test)[1]
        y_test_pred = np.array(list(map(lambda x: 1 if x > 0.5 else 0, y_test_pred_prob)))
        acc = np.sum(y_test_pred - y_test == 0) / y_test.shape[0]
        y_test_pred = np.array(y_test_pred)
        y_test_pred_prob = np.array(y_test_pred_prob)
        return y_test_pred, y_test_pred_prob, acc
