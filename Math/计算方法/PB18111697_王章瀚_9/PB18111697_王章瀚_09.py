import numpy as np
import math


def f(x, y):
    return -x*x*y*y


def accu_y(x):
    return 3/(1+x**3)


def Runge_Kutta_4(f, h, x, y, xn):
    n = int((xn-x)/h)
    for i in range(n):
        k1 = f(x, y)
        k2 = f(x+h*0.5, y+h*k1*0.5)
        k3 = f(x+h*0.5, y+h*k2*0.5)
        k4 = f(x+h, y+h*k3)
        y = y + h*(k1+2*k2+2*k3+k4)/6
        x = x + h
    return y


def Adams_Implicit_4(f, h, x0, y0, xn):
    n = int((xn-x0)/h)-3
    x0, y0 = x0, accu_y(x0)
    x1 = x0 + h
    y1 = accu_y(x1)
    x2 = x1 + h
    y2 = accu_y(x2)
    x3 = x2 + h
    y3 = accu_y(x3)
    for i in range(n):
        y = y3 + h*(55*f(x3, y3) - 59*f(x2, y2) + 37*f(x1, y1) - 9*f(x0, y0))/24
        y = y3+h*(9*f(x3+h, y) + 19* f(x3, y3) - 5*f(x2, y2) + f(x1, y1))/24
        x0, x1, x2, x3, y0, y1, y2, y3 = x1, x2, x3, x3+h, y1, y2, y3, y
    return y
    
    
def main():
    target_x = 1.5
    l_max = 3
    
    h = []
    err = []
    ok = []
    for l in range(l_max+1):
        h.append(0.1/(2**l))
        y = Runge_Kutta_4(f, h[-1], 0, 3, target_x)
        err.append(y-accu_y(target_x))
    for i in range(l_max):
        ok.append(math.log(err[i]/err[i+1])/math.log(2))
    ok.append(math.nan)
    print('四阶Runge-Kutta公式的误差和误差阶：')
    for l in range(l_max+1):
        print('h={:.15f}, err={:.15e}, ok={:.15e}'.format(h[l], err[l], ok[l]))
    
    h = []
    err = []
    ok = []
    for l in range(l_max+1):
        h.append(0.1/(2**l))
        y = Adams_Implicit_4(f, h[-1], 0, 3, target_x)
        err.append(y-accu_y(target_x))
    for i in range(l_max):
        ok.append(math.log(err[i]/err[i+1])/math.log(2))
    ok.append(math.nan)
    print('四阶隐式Adams公式的误差和误差阶：')
    for l in range(l_max+1):
        print('h={:.15f}, err={:.15e}, ok={:.15e}'.format(h[l], err[l], ok[l]))
        
    
    


if __name__ == '__main__':
    main()
