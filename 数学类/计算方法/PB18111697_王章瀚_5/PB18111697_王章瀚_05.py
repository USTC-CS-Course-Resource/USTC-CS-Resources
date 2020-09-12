import numpy as np
import math

# 一些初值
initial1 = [0.1, 0.2, 0.9, 9.0]
initial2 = [[-0.1, 0.1], [-0.2, 0.2], [-2.0, 0.9], [0.9, 9.0]]
e = 1.0e-8


def f(x):
    return x**3/3-x


def df(x):
    return x**2-1


root = [0, 3**0.5, -3**0.5]


def Newton(x0, f, df, e):
    n = 1
    x1 = x0-f(x0)/df(x0)
    es = []
    while abs(x1-x0) >= e:
        es.append(abs(x1-x0))
        x0 = x1
        n += 1
        x1 = x0-f(x0)/df(x0)
    return x1, n, es


def Secant(x0, x1, f, e):
    n = 1
    x2 = x1-f(x1)*(x1-x0)/(f(x1)-f(x0))
    es = []
    while abs(x2-x1) >= e and abs(f(x2)) >= e:
        es.append(abs(x2-x1))
        x1, x0 = x2, x1
        n += 1
        x2 = x1-f(x1)*(x1-x0)/(f(x1)-f(x0))
    return x2, n, es
    
    
def ErrorOrder(es, order):
    return [es[i+1]/es[i]**order for i in range(len(es)-1)]

def main():
    for x in initial1:
        r, n, es = Newton(x, f, df, e)
        print("初值={{x0={:.1f}}}, 根={:.15e}, 迭代步数={:d}".format(x, r, n))
        print(ErrorOrder(es, 2))
        
      
    for x in initial2:
        r, n, es = Secant(x[0], x[1], f, e)
        print("初值={{x0={:.1f},x1={:.1f}}}, 根={:.15e}, 迭代步数={:d}".format(x[0], x[1], r, n))
        #print(ErrorOrder(es, 2))
    
    
if __name__ == '__main__':
    main()
    



