from matplotlib import pyplot as plt
import numpy as np
plt.ion()
# Données physiques
pi=3.1415
G=6.6741e-11

R_exp=6.96e8
M_exp=1.99e30

# Données du modèle
n=3.
P_c=3.00e16
rho_c=1.53e5
K=P_c/(rho_c**(1.+1./n))
R=((1./(4*pi*G))*(n+1.)*K*rho_c**(-1.+1./n))**(1./2.)
M=4*pi*rho_c*R**3


folder="../resultats/"
results=np.loadtxt(folder+"resultats_differents_n/resultats_n"+str(int(n))+".dat")

if len(results[1])==3:
    z,w_calc,q_calc=results.T    
else:
    z,w_calc,w_exact,q_calc=results.T
    rho_exact=(w_exact**n)*rho_c
    P_exact=K*rho_exact**(1.+1./n)


limite=500
r=z[:limite]*R
rho_calc=rho_c*w_calc[:limite]**n
P_calc=K*rho_c*w_calc[:limite]**(n+1.)
m_calc=q_calc[:limite]*M


R_calc=min(r[rho_calc<0.])
print ("rayon au bord calculé = ","%.2E" % R_calc, " , rayon au bord expérimental = ","%.2E" % R_exp, " , erreur = ","%.2E" % abs( R_calc - R_exp ))

M_calc=min(m_calc[rho_calc<0.])
print ("masse totale calculé = ","%.2E" % M_calc, " , masse totale expérimentale = ","%.2E" % M_exp, " , erreur = ","%.2E" % abs( M_calc - M_exp ))

print ("erreur rayon = ", abs( R_calc - R_exp )/R_exp, " , erreur masse = ", abs( M_calc - M_exp )/M_exp)

plt.figure(1)
plt.axes(xlabel='rayon (m)',ylabel='densité (kg.m^-3)')
plt.plot(r,rho_calc,'.r')
plt.legend(('rho_calc',' '))
plt.title("Densité en fonction du rayon")

plt.figure(2)
plt.clf()
plt.axes(xlabel='rayon (m)',ylabel='pression (N.m^-2)')
plt.plot(r,P_calc,'.r')
plt.legend(('P_calc',' '))
plt.title("Pression en fonction du rayon")

plt.figure(3)
plt.clf()
plt.axes(xlabel='rayon (m)',ylabel='masse (kg)')
plt.plot(r,m_calc,'.r')
plt.legend(('m_calc',' '))
plt.title("Masse en fonction du rayon")


