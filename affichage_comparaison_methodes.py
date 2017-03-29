from matplotlib import pyplot as plt
import numpy as np

results=np.loadtxt("resultats_comparaison_methodes.dat")

i,t_NR,steps_NR,t_dichotomie,steps_dichotomie=results.T

plt.figure(1)
plt.title("Comparaison de 2 methodes de resolution d equation non lineaire")
plt.suptitle("Dichotomie dans l'intervalle : [0,i] ; Valeur de depart pour Newton : i")
plt.axes(xlabel='valeur de depart i',ylabel='temps de calcul')
plt.plot(i,t_NR,'.r',i,t_dichotomie,'.b')
plt.legend(('Newton','Dichotomie'))

plt.show(1)


plt.figure(2)
plt.clf()
plt.axes(xlabel='valeur de depart i',ylabel='nombre d\'etapes',yscale='log')
plt.plot(i,steps_NR,'.r',i,steps_dichotomie,'.b')
plt.legend(('Newton','Dichotomie'))

plt.show(2)
