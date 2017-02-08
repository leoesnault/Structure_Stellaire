from matplotlib import pyplot as plt
import numpy as np

results=np.loadtxt("results.dat")

if len(results[0])==3:
    z,w_calc,q=results.T
    plt.axes(xlabel='z')
    plt.plot(z,w_calc,'.r',z,q,'.b')
    plt.legend(('w_calc','q'))
else:
    z,w_calc,w_exact,q=results.T
    plt.axes(xlabel='z')
    plt.plot(z,w_calc,'.r',z,w_exact,'r',z,q,'.b')
    plt.legend(('w_calc','w_exact','q'))


plt.show()
