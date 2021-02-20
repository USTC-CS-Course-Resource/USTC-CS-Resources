import numpy as np
import random
import matplotlib.pyplot as plt


class KMeans:
    def __init__(self, n_clusters=3, tol=0.0001, init='random', stopby='class'):
        assert init == 'random' or init == 'sample'
        assert stopby == 'class' or stopby == 'tol'
        self.data = None
        self.n_clusters = n_clusters
        self.tol = tol
        self.means = None
        self.init = init
        self.stopby = stopby
        random.seed(18111697)
        np.random.seed(18111697)

    def draw(self, x, means, class_mask, ax=None, label='diagram'):
        assert x.shape[0] == class_mask.shape[0]
        if ax:
            plt.cla()
            for i, c in enumerate(['r', 'b', 'g']):
                ax.scatter(x[class_mask == i][:, 0], x[class_mask == i][:, 1], c=c, label=f'class_{i}')
                ax.scatter(means[i][0], means[i][1], c=c, marker='+', s=256, linewidth=4)
            plt.legend()
            plt.title(label)
            plt.pause(0.3)
        else:
            plt.ioff()
            print(means)
            fig = plt.figure()
            ax = fig.add_subplot(1,1,1)

            for i, c in enumerate(['r', 'b', 'g']):
                ax.scatter(x[class_mask == i][:, 0], x[class_mask == i][:, 1], c=c, label=f'class_{i}')
                ax.scatter(means[i][0], means[i][1], c=c, marker='+', s=256, linewidth=4)
            plt.legend()
            plt.title(label)
            plt.show()
            plt.ion()

    def fit(self, x, ax=None):
        xmax = x.max()
        xmin = x.min()
        m = x.shape[0]
        if self.init == 'random':
            means = np.random.randn(self.n_clusters, x.shape[1])
        elif self.init == 'sample':
            means = np.array(random.choices(x, k=self.n_clusters))
        else:
            assert False
        class_mask = -np.ones(m, dtype=np.int)
        iter = 0
        while True:
            iter += 1
            new_class_mask = np.array([np.argmin([np.sum((xi - mean) ** 2) for mean in means])
                                       for xi in x])
            if self.stopby == 'class' and np.sum(class_mask != new_class_mask) == 0:
                break
            class_mask = new_class_mask
            new_means = np.array([x[class_mask == c].mean(axis=0)
                                  if np.sum(class_mask == c) != 0 else np.random.uniform(xmin, xmax, size=x.shape[1])
                                  for c in range(self.n_clusters)])
            if self.stopby == 'tol' and np.sum((new_means - means) > self.tol) == 0:
                break
            means = new_means
            if ax:
                self.draw(x, means, class_mask, ax, f'iter {iter}')
        self.means = means
        if ax:
            self.draw(x, means, class_mask, ax, f'iter {iter}')
        return iter

    def predict(self, x):
        pred_y = np.array([np.argmin([np.sum((xi - mean) ** 2) for mean in self.means])
                           for xi in x])
        return pred_y

    def score_dbi(self, x):
        pred_y = self.predict(x)
        # print(np.array([[np.sqrt(np.sum((xinc - self.means[c]) ** 2)) if xinc.shape[0] > 0 else 0
        #                          for xinc in x[pred_y == c]]
        #        for c in range(self.n_clusters)]).shape)
        avg = np.array([np.mean([np.sqrt(np.sum((xinc - self.means[c]) ** 2))
                                 for xinc in x[pred_y == c]]) if np.sum(pred_y == c) > 0 else np.inf
                        for c in range(self.n_clusters)])
        dcen = np.array([[np.sqrt(np.sum((self.means[row] - self.means[col]) ** 2))
                          for col in range(self.n_clusters)]
                         for row in range(self.n_clusters)])
        dbi = np.mean([np.max([(avg[i] + avg[j]) / dcen[i][j] for j in range(self.n_clusters) if i != j])
                       for i in range(self.n_clusters)])
        if dbi == np.inf:
            self.draw(x, self.means, pred_y)
        return dbi

    def score(self, x, y, criterion='dbi'):
        """
        :param criterion: score criterion, which could be a str or list of str
        :return:
        """
        if type(criterion) == str:
            if criterion == 'dbi':
                return self.score_dbi(x)
        return None


if __name__ == '__main__':
    raw_data = dict(np.load("../k-means/k-means.npy", allow_pickle=True).item())
    raw_data[0] = np.array(raw_data.pop('class_0'))
    raw_data[1] = np.array(raw_data.pop('class_1'))
    raw_data[2] = np.array(raw_data.pop('class_2'))

    data_x = np.r_[raw_data[0], raw_data[1], raw_data[2]]
    data_y = np.array([0] * raw_data[0].shape[0] + [1] * raw_data[1].shape[0] + [2] * raw_data[2].shape[0])
    kmeans = KMeans(n_clusters=3, tol=0.001, init='random', stopby='tol')
    fig = plt.figure()
    plt.ion()
    ax = fig.add_subplot(1, 1, 1)
    iter = kmeans.fit(data_x, ax)
    print(f'iterations: {iter}')
    score = kmeans.score(data_x, data_y)
    print(f'cluster center: \n{kmeans.means}')
    print(f'dbi: {score}')
    plt.pause(2)
