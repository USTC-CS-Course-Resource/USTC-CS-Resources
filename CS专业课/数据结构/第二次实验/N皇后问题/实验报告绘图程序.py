import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import numpy as np

N = np.array(range(4, 13))
stack=[0.0000736,0.0001495,0.0007673,0.0027767,0.0104837,
       0.048083,0.228105,1.2051,6.8581]
recursion=[0.0000035,0.0000092,0.0000458,0.0001814,0.0006057,
           0.0029883,0.0137117,0.0739021,0.421939]

def func(x, a, b):
    return a*np.exp(b*x)

stack_popt, stack_pcov = curve_fit(func, N, stack)
recursion_popt, recursion_pcov = curve_fit(func, N, recursion)

plt.figure(figsize=(9,9))
plt.subplot(1, 2, 1)
plt.scatter(N, stack, color='red')
x = np.linspace(0, 12, 100)
y = [func(t, *stack_popt) for t in x]
plt.plot(x, y, color='gray')
plt.legend(['{:.2e}*exp({:.2e}x)'.format(*stack_popt), 'stack'])
plt.subplot(1, 2, 2)
plt.scatter(N, recursion, color='blue')
x = np.linspace(0, 12, 100)
y = [func(t, *recursion_popt) for t in x]
plt.plot(x, y, color='gray')
plt.legend(['{:.2e}*exp({:.2e}x)'.format(*recursion_popt), 'recursion'])
