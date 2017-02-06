from matplotlib import pyplot as plt
import numpy as np

results=np.loadtxt("results.dat")

if len(results[0])==3:
    z,q,w_calc=results.T
    plt.axes(xlabel='z')
    plt.plot(z,q,'ob',z,w_calc,'or')
    plt.legend(('q','w_calc'))
else:
    z,q,w_calc,w_exact=results.T
    plt.axes(xlabel='z')
    plt.plot(z,q,'ob',z,w_calc,'or',z,w_exact,'r')
    plt.legend(('q','w_calc','w_exact'))


plt.show()
