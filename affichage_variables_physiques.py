from matplotlib import pyplot as plt
import numpy as np

results=np.loadtxt("resultats.dat")

# // resultats_variables_physiques
# // << z[i]/A << "		"
# // << K*pow(pow(w[i],n)*rho_c,float(n+1)/float(n)) << "		"
# // << K*pow(pow(w_exact[i],n)*rho_c,float(n+1)/float(n)) << "		"
# // << pow(w[i],n)*rho_c << "		"
# // << pow(w_exact[i],n)*rho_c << "		"
# // << q[i]*M << endl;

# pi=3.1415
# G=6.6741e-11
# R=6.9634e8
# M=1.9891e30
# K=5e7
# n=1.

# P_c=(2.*G/pi*pow(R,4))
# rho_c=pow((P_c/K),n/(n+1))
# A=sqrt(4.*pi*G/(float(n+1)*K*pow(rho_c,(1-n)/n)));

if len(results[1])==3:
    z,w_calc,q=results.T
    plt.axes(xlabel='z')
    plt.plot(z,w_calc,'.r',z,q,'.b')
    plt.legend(('w_calc','q'))
else:
    z,w_calc,w_exact,q=results.T
    plt.axes(xlabel='z')#,yscale='log'
    plt.plot(z,w_calc,'.r',z,w_exact,'r',z,q,'.b')
    plt.legend(('w_calc','w_exact','q'))


plt.show()
