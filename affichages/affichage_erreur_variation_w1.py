from matplotlib import pyplot as plt
import numpy as np

folder="../resultats/"

results_00=np.loadtxt(folder+"resultats_variation_w1/resultats_00pc.dat")

results_p01=np.loadtxt(folder+"resultats_variation_w1/resultats_plus_01pc.dat")
results_p05=np.loadtxt(folder+"resultats_variation_w1/resultats_plus_05pc.dat")
results_p10=np.loadtxt(folder+"resultats_variation_w1/resultats_plus_10pc.dat")
results_p20=np.loadtxt(folder+"resultats_variation_w1/resultats_plus_20pc.dat")

results_m01=np.loadtxt(folder+"resultats_variation_w1/resultats_moins_01pc.dat")
results_m05=np.loadtxt(folder+"resultats_variation_w1/resultats_moins_05pc.dat")
results_m10=np.loadtxt(folder+"resultats_variation_w1/resultats_moins_10pc.dat")
results_m20=np.loadtxt(folder+"resultats_variation_w1/resultats_moins_20pc.dat")

z00,w_calc00,w_exact00,q00=results_00.T

zp01,w_calcp01,w_exactp01,qp01=results_p01.T
zp05,w_calcp05,w_exactp05,qp05=results_p05.T
zp10,w_calcp10,w_exactp10,qp10=results_p10.T
zp20,w_calcp20,w_exactp20,qp20=results_p20.T

zm01,w_calcm01,w_exactm01,qm01=results_m01.T
zm05,w_calcm05,w_exactm05,qm05=results_m05.T
zm10,w_calcm10,w_exactm10,qm10=results_m10.T
zm20,w_calcm20,w_exactm20,qm20=results_m20.T

plt.axes(xlabel='z')
plt.plot(z00,w_exact00-w_calc00,'.-',zp05,w_exactp05-w_calcp05,'.-',zp10,w_exactp10-w_calcp10,'.-',zm05,w_exactm05-w_calcm05,'.-',zm10,w_exactm10-w_calcm10,'.-')
plt.legend(('erreur(0 % de variation)','erreur(+5% de variation)','erreur(+10% de variation)','erreur(-5% de variation)','erreur(-10% de variation)'))
plt.grid()
plt.title("Erreur sur la densité adimensionnée en fonction du rayon adimensionné, pour un schéma à gauche et n=1")

N=[-20,-10,-5,0,5,10,20]
erreur=np.linspace(0,8,7)
erreur[0]=max(abs(w_exactm20-w_calcm20))
erreur[1]=max(abs(w_exactm10-w_calcm10))
erreur[2]=max(abs(w_exactm05-w_calcm05))
erreur[3]=max(abs(w_exact00-w_calc00))
erreur[4]=max(abs(w_exactp05-w_calcp05))
erreur[5]=max(abs(w_exactp10-w_calcp10))
erreur[6]=max(abs(w_exactp20-w_calcp20))

plt.figure(2)
plt.axes(xlabel='variation de w[1] (en %)')
plt.plot(N,erreur,'.-')
plt.grid()
plt.legend(('erreur',''))
plt.title("Erreur maximale entre la solution exacte et calculée en fonction de la variation de w[1], pour un schéma à gauche et n=1")

plt.show()