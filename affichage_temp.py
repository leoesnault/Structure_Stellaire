from matplotlib import pyplot as plt
import numpy as np

results=np.loadtxt("resultats_temp.dat")

z,w_calc,w_exact=results.T
plt.axes(xlabel='z')
plt.plot(z,w_calc,'.r',z,w_exact,'.b')
plt.legend(('w_calc','w_exact'))

plt.show()
