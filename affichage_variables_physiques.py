from matplotlib import pyplot as plt
import numpy as np

results=np.loadtxt("resultats_variables_physiques.dat")

if len(results[0])==4:
    r,rho_calc,P_calc,m=results.T
    plt.axes(xlabel='r',yscale='log')
    plt.plot(r,m,'ob',r,rho_calc,'or',r,P_calc,'og')
    plt.legend(('m','rho_calc','P_calc'))
else:
    r,rho_calc,rho_exact,P_calc,P_exact,m=results.T
    plt.axes(xlabel='r',yscale='log')
    plt.plot(r,m,'ob',r,rho_calc,'or',r,rho_exact,'r',r,P_calc,'og',r,P_exact,'g')
    plt.legend(('m','rho_calc','rho_exact','P_calc','P_exact'))


plt.show()
