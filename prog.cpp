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
#include <physiconstants> // contient les constantes physiques usuelles
using namespace std;
// ----




// Données physiques
const double G=6.67e-11,pi=3.14; // constantes physiques et mathématiques
double M=1.9891e30,R=6.96342e8,n=3./2.,K=2.e16; // Masse totale, rayon, indice polytropique et constante polytropique(a trouver)
double P_c=(2.*G/pi*pow(R,4)),rho_c=pow((P_c/K),n/(n+1)); // estimation pression et densité au centre
double A=(M/(pow(R,3)*rho_c)),B=(M/(pow(R,4)*P_c)); // valeurs des constantes A et B
//float u=(d ln(M))/(d ln(r)),v=-(d ln(P))/(d ln(r)); // variables de Milne
// ----


// Variables relatives aux calculs
const int N=10; // nombre de noeuds de la grille de calcul
const double h=M/N; // pas de masse
double m[N+1],r[N+1],P[N+1],rho[N+1];
// ----


// Définition des fonctions





// ----







int main()
{
	// Affichage d'informations sur le calcul
	cout << "Modèle polytropique de structure stellaire pour une étoile de rayon "<<R<<"m et de masse "<<M<<"kg."<<endl;
	cout <<"P_c = "<< P_c << "   rho_c = "<< rho_c << "   A = " << A << "   B = "<< B << endl;
	// ----
	// Rho doit être de l'ordre de 1.50e5 kg.m^-3 au centre
	
	// Définition du fichier de sortie
	ofstream results("results.dat");
	// ----
	
	// Définition des conditions au centre
	m[0]=0.;
	r[0]=0.; // !!!!!
	P[0]=1.;
	rho[0]=1.;
	// ----
	
	
	for (unsigned int i = 1; i <= N; i += 1)
	{
		m[i]=double(i)/double(N);
		r[i]=h/(4.*pi*pow(r[i-1],4)*rho[i-1]) + r[i-1]; // problème en 0 !
		P[i]=-(G*h/(4.*pi*pow(r[i-1],4)))*B+P[i-1];
		rho[i]=pow((P[i]/K),n/(n+1));
		results << m[i] << "    " << r[i] << "    " << P[i] << "    " << rho[i] << endl;
		cout << m[i] << "    " << r[i] << "    " << P[i] << "    " << rho[i] << endl;
	}
	
	
}
