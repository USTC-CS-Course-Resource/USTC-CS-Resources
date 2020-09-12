import math
import numpy as np


def f(x):
    return math.sin(x)


def If(a, b):
    return math.cos(a) - math.cos(b)


# 复化梯形积分公式
# 返回数值积分值
def Trapezoid(a, b, N, func):
    xs = np.linspace(a, b, N)
    h = (b-a)/(N-1)
    I = h*(func(a)/2
            + np.sum([func(x) for x in xs[1:N-1]])
            + func(b)/2)
    return I


# 复化Simpson积分公式
# 返回数值积分值
def Simpson(a, b, N, func):
    xs = np.linspace(a, b, N)
    h = 2*(b-a)/(N-1)
    I = h/6*(func(a)
             + np.sum([func(xs[k]) * (2+2*(k % 2)) for k in range(1, N-1)])
             + func(b))
    return I


# 给定误差列表e
# 返回误差阶o2列表
def o2(e):
    return [math.log(math.nan if i == 0 else abs(e[i-1]/e[i]))/math.log(2) for i in range(len(e))]


def main():
    a = 1
    b = 5
    MAX_L = 12
    print("复化梯形积分：")
    I = [Trapezoid(a, b, 1+int(math.pow(2, i)), f) for i in range(1, MAX_L+1)]
    e = [If(a, b) - i for i in I]
    o = o2(e)
    for i in range(MAX_L):
        print("{:.15f}, {:.15f}, {:.15f}".format(I[i], e[i], o[i]))
    print()

    print("复化Simpson积分：")
    I = [Simpson(a, b, 1+int(math.pow(2, l)), f) for l in range(1, MAX_L+1)]
    e = [If(a, b) - i for i in I]
    o = o2(e)
    for i in range(MAX_L):
        print("{:.15f}, {:.15f}, {:.15f}".format(I[i], e[i], o[i]))


if __name__ == '__main__':
    main()


