from matplotlib import pyplot as plt
import numpy as np

folder="../resultats/"


results_N0100=np.loadtxt(folder+"resultats_variation_N/resultats_N0100.dat")
results_N0200=np.loadtxt(folder+"resultats_variation_N/resultats_N0200.dat")
results_N0600=np.loadtxt(folder+"resultats_variation_N/resultats_N0600.dat")
results_N1000=np.loadtxt(folder+"resultats_variation_N/resultats_N1000.dat")
results_N1325=np.loadtxt(folder+"resultats_variation_N/resultats_N1325.dat")
results_N2550=np.loadtxt(folder+"resultats_variation_N/resultats_N2550.dat")
results_N3775=np.loadtxt(folder+"resultats_variation_N/resultats_N3775.dat")
results_N5000=np.loadtxt(folder+"resultats_variation_N/resultats_N5000.dat")

z0100,w_calc0100,w_exact0100,q0100=results_N0100.T
z0200,w_calc0200,w_exact0200,q0200=results_N0200.T
z0600,w_calc0600,w_exact0600,q0600=results_N0600.T
z1000,w_calc1000,w_exact1000,q1000=results_N1000.T
z1325,w_calc1325,w_exact1325,q1325=results_N1325.T
z2550,w_calc2550,w_exact2550,q2550=results_N2550.T
z3775,w_calc3775,w_exact3775,q3775=results_N3775.T
z5000,w_calc5000,w_exact5000,q5000=results_N5000.T

plt.axes(xlabel='z')
plt.plot(z0100,w_exact0100-w_calc0100,'.-',z0200,w_exact0200-w_calc0200,'.-',z0600,w_exact0600-w_calc0600,'.-',z1000,w_exact1000-w_calc1000,'.-',z1325,w_exact1325-w_calc1325,'.-',z2550,w_exact2550-w_calc2550,'.-',z3775,w_exact3775-w_calc3775,'.-',z5000,w_exact5000-w_calc5000,'.-')
plt.legend(('erreur(N=100)','erreur(N=200)','erreur(N=600)','erreur(N=1000)','erreur(N=1325)','erreur(N=2550)','erreur(N=3775)','erreur(N=5000)'))
plt.grid()
plt.title("Erreur sur la densité adimensionnée en fonction du rayon adimensionné, pour un schéma à gauche et n=1")

N=[100,200,600,1000,1325,2550,3775,5000]
erreur=np.linspace(0,8,8)
erreur[0]=max(w_exact0100-w_calc0100)
erreur[1]=max(w_exact0200-w_calc0200)
erreur[2]=max(w_exact0600-w_calc0600)
erreur[3]=max(w_exact1000-w_calc1000)
erreur[4]=max(w_exact1325-w_calc1325)
erreur[5]=max(w_exact2550-w_calc2550)
erreur[6]=max(w_exact3775-w_calc3775)
erreur[7]=max(w_exact5000-w_calc5000)

plt.figure(2)
plt.axes(xlabel='N')
plt.plot(N,erreur,'.-')
plt.grid()
plt.legend(('erreur',''))
plt.title("Erreur maximale entre la solution exacte et calculée, pour un schéma à gauche et n=1")

plt.show()