import numpy as np
import matplotlib.pyplot as plt

# speedup for different #thread
x = np.array([1,2,4,8,16])
idea = np.linspace(0, 16, 100)
speedup = np.array([0.914382,1.70616,3.354127,6.374795,8.355579])
plt.plot(idea, idea, linestyle='--',c='green',label='ideal')
plt.plot(x, speedup, c='red',label='result')
plt.scatter(x, speedup, c='red')
plt.xlabel('#thread')
plt.ylabel('speedup')
plt.legend()
plt.show()


# performance for different algorithm
data_size = [1e2,1e3,1e4,1e5,1e6,1e7,1e8]
qsort_time = [2118,27347,350337,4207802,48754399,577245529,6797659276]
psrs_time = [122776,109961,244583,1395777,15271155,169966541,1945353220]

ax = plt.gca()
ax.set_xscale('log')
ax.set_yscale('log')
plt.scatter(data_size, qsort_time, c='cyan', marker='o', label='std::sort')
plt.scatter(data_size, psrs_time, c='deeppink', marker='^', label='PSRS')
plt.plot(data_size, qsort_time, c='cyan')
plt.plot(data_size, psrs_time, c='deeppink')
plt.xlabel("data size")
plt.ylabel('time cost(ns)')
plt.legend()
plt.show()
