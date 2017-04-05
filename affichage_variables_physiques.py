from matplotlib import pyplot as plt
import numpy as np

# Données physiques
pi=3.1415
G=6.6741e-11

R_exp=6.9634e8
M_exp=1.9891e30

# Données du modèle ...
n=3.
P_c=
rho_c=
K=P_c/(rho_c**(1.+1./n))

results=np.loadtxt("resultats_schema_gauche/resultats_n3.dat")

if len(results[1])==3:
    z,w_calc,q=results.T
    
    r=z/A
    rho_calc=pow(w_calc,n)*rho_c
    P_calc=K*pow(rho_calc,1.+1./n)
    m=q*M
    
    plt.axes(xlabel='r')
    plt.plot(r,rho_calc,'.r')#,r,P_calc,'.b',r,m,'.g')
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
