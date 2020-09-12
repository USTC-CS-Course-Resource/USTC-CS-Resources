import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def f(x, a):
    return a*x*x


x = [5,	10,	20,	40,	50,	100	,300,	500]
y = [11,	36	,139.6666667	,554.3333333	,882.6666667,	3384.333333	,31431,	85637.33333]

popt, pcov = curve_fit(f, x, y)

plt.scatter(x, y, label="raw data", color='red')
xx = np.linspace(0, 500, 2000)
yy = xx*xx*popt[0]
plt.plot(xx, yy, label=u"fitted curve: {:.5e}x^2".format(popt[0]))
plt.legend()
plt.xlabel("size of numbers")
plt.ylabel("time consumed/ms")


plt.show()
