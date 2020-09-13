import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import numpy as np

x = [9.22,19.178,20.94,21.765,23.154,11.90,13.924,15.832,16.314]
y = [7,68,77,86,95,12,28,36,39]

def func(x, a, b):
    return a*x+b

popt, pcov = curve_fit(func, np.multiply(x, x), y)

plt.figure(figsize=(9,9))
plt.scatter(np.multiply(x, x), y, color='red')
x = np.linspace(80, 550, 1000)
y = [func(t, *popt) for t in x]
plt.plot(x, y, color='gray')
plt.legend(['{:.2f}*exp({:.2f}x)'.format(*popt), 'original data'])
plt.xlim(70, 570)
plt.ylim(0,100)
plt.xlabel("I am x")
plt.ylabel("I am y")