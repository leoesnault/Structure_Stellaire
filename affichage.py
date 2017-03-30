from matplotlib import pyplot as plt
import numpy as np

results=np.loadtxt("resultats.dat")

if len(results[1])==3:
    z,w_calc,q=results.T
    plt.axes(xlabel='z')
    plt.plot(z,w_calc,'.r')#,z,q,'.b')
    plt.legend(('w_calc','q'))
    plt.grid()
    plt.title("Évolution de la densité adimensionnée en fonction du rayon adimensionné, pour un schéma à gauche et n=3/2")
else:
    z,w_calc,w_exact,q=results.T
    plt.axes(xlabel='z')#,yscale='log'
    plt.plot(z,w_calc,'.r',z,w_exact,'r')#,z,q,'.b')
    plt.legend(('w_calc','w_exact','q'))
    plt.title("Évolution de la densité adimensionnée en fonction du rayon adimensionné, pour un schéma à gauche et n=1")
    plt.grid()
    plt.figure(2)
    plt.axes(xlabel='z')
    plt.plot(z,w_exact-w_calc,'.-')
    plt.legend(('w_exact-w_calc'))
    plt.title("Erreur en fonction du rayon adimensionné, pour un schéma à gauche et n=1")
    
plt.show()