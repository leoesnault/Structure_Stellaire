from matplotlib import pyplot as plt
import numpy as np

results=np.loadtxt("resultats_comparaison_methodes.dat")

i,t_NR,t_dichotomie=results.T

# plt.title("Comparaison de 2 méthodes de résolution d'équation non linéaire")
# plt.suptitle("Dichotomie dans l'intervalle : [0,i] ; Valeur de départ pour Newton : i")
plt.axes(xlabel='valeur de départ i',ylabel='temps de calcul')
plt.plot(i,t_NR,'.r',i,t_dichotomie,'.b')
plt.legend(('Newton','Dichotomie'))


plt.show()
