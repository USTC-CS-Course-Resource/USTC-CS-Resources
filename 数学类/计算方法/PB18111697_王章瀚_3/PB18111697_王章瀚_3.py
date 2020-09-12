import numpy as np
import matplotlib.pyplot as plt

# 数据
x = [0.25, 0.50, 0.75, 1.00, 1.25, 1.50, 1.75, 2.00, 2.25, 2.50]
y = [1.284, 1.648, 2.117, 2.718, 3.427, 2.798, 3.534, 4.456, 5.465, 5.894]

# 按最小二乘法，A'At = A'Y
# 下述M为A'A， N为A'Y

# A'A
M = [[np.sum(np.square(np.sin(x))), np.sum(np.multiply(np.sin(x), np.cos(x)))],
     [np.sum(np.multiply(np.sin(x), np.cos(x))), np.sum(np.square(np.cos(x)))]]

# A'Y
N = [np.sum(np.multiply(y, np.sin(x))), np.sum(np.multiply(y, np.cos(x)))]

# 由克莱姆法则
a = (N[0]*M[1][1]-N[1]*M[0][1])/(M[0][0]*M[1][1]-M[0][1]*M[1][0])
b = (N[1]*M[0][0]-N[0]*M[1][0])/(M[0][0]*M[1][1]-M[0][1]*M[1][0])

y_ = np.add(a*np.sin(x),b*np.cos(x))
error = np.square(np.subtract(y_, y)).mean()

print("a = {:.15f}, b = {:.15f}, 均方误差 = {:.15f}".format(a, b, error))

'''
plt.subplot(1, 1, 1)
plt.scatter(x, y, color = 'orange')
plt.plot(x, y_)
'''

