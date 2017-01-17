/*
Programme de calcul de structure stellaire, utilisant les hypothèses :
-Gaz autogravitant à l'équilibre
-Chimiquement homogène
-Sans rotation propre
-Équation d'état polytropique
-Solutions à une dimension
-
*/



// Librairies utilisées
#include <iostream> // contient cin, cout ...
#include <fstream> // permet de lire et écrire dans un fichier
#include <cmath> // contient des fonctions mathématiques usuelles
using namespace std;
// ----




// Données physiques
float M=2.e33,R,rho,n=3./2.,K; // Masse totale, rayon, densité, indice polytropique et cte polytropique,
float P_c, T_c; // estimation pression, température au centre
float u=(d ln(M))/(d ln(r)),v=-(d ln(P))/(d ln(r)); // variables de Milne
// ----


// Variables relatives aux calculs
int N=100; // nombre de noeuds de la grille de calcul
float h=M/N; // pas de masse

// ----


// Définition des fonctions





// ----







int main()
{







}
