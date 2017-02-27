from matplotlib import pyplot as plt
import numpy as np

# Données physiques et du problème
pi=3.1415
G=6.6741e-11

R=6.9634e8
M=1.9891e30
K=5e7
n=1.

P_c=(2.*G/pi*pow(R,4))
rho_c=pow((P_c/K),n/(n+1))
A=pow(4.*pi*G/(float(n+1)*K*pow(rho_c,(1-n)/n)),1./2.);


results=np.loadtxt("resultats.dat")

if len(results[1])==3:
    z,w_calc,q=results.T
    
    r=z/A
    rho_calc=pow(w_calc,n)*rho_c
    P_calc=K*pow(rho_calc,1.+1./n)
    m=q*M
    
    plt.axes(xlabel='z',yscale='log')
    plt.plot(r,rho_calc,'.r',r,P_calc,'.b',r,m,'.g')
    plt.legend(('rho_calc','P_calc','m'))
else:
    z,w_calc,w_exact,q=results.T
    
    r=z/A
    rho_calc=pow(w_calc,n)*rho_c
    rho_exact=pow(w_exact,n)*rho_c
    P_calc=K*pow(rho_calc,1.+1./n)
    P_exact=K*pow(rho_exact,1.+1./n)
    m=q*M
    
    plt.axes(xlabel='z',yscale='log')
    plt.plot(r,rho_calc,'.r',r,rho_exact,'r',r,P_calc,'.b',r,P_exact,'b',r,m,'.g')
    plt.legend(('rho_calc','rho_exact','P_calc','P_exact','m'))


plt.show()
