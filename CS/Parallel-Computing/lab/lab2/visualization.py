import numpy as np
import matplotlib.pyplot as plt
from numpy.lib.function_base import _quantile_is_valid

# PI computing
x = np.array([1,2,4,8,16])
idea = np.linspace(1, 16, 100)
speed = 1 / np.array([1002967915, 522141233, 270407752, 198152524, 145617106])
plt.plot(idea, (idea - 1) * speed[0] + speed[0], linestyle='--',c='cyan',label='ideal')
plt.plot(x, speed, c='red',label='result')
plt.scatter(x, speed, c='red')
plt.xlabel('#process')
plt.ylabel(r'$speed=\frac{1}{time\ cost}$')
plt.legend()
plt.show()

# speedup for different #thread
x = np.array([1,2,4,8,16])
idea = np.linspace(0, 16, 100)
speed = 1 / np.array([6919596034,4046962291,2223212791,1398991919	,1268076705])
plt.plot(idea, (idea - 1) * speed[0] + speed[0], linestyle='--',c='cyan',label='ideal')
plt.plot(x, speed, c='red',label='result')
plt.scatter(x, speed, c='red')
plt.xlabel('#process')
plt.ylabel(r'$speed=\frac{1}{time\ cost}$')
plt.legend()
plt.show()


# performance for different algorithm
data_size = [1e2,1e3,1e4,1e5,1e6,1e7,1e8]
qsort_time = np.array([1909,26841,347211,4460476,53265060,600714131,7943134440])
psrs_time = np.array([247480,249792,432954,2168342,17889299,194817606,2270424459])

ax = plt.gca()
ax.set_xscale('log')
ax.set_yscale('log')
# plt.ylim(0, 1 / 200000)
print(1/qsort_time)
plt.scatter(data_size, qsort_time, c='cyan', marker='o', label='std::sort')
plt.scatter(data_size, psrs_time, c='deeppink', marker='^', label='PSRS')
plt.plot(data_size, qsort_time, c='cyan')
plt.plot(data_size, psrs_time, c='deeppink')
plt.xlabel("data size")
plt.ylabel(r'time cost')
plt.legend()
plt.show()
