/*
Programme de calcul de structure stellaire permettant de résoudre l'équation de Lane-Emden

A faire :
-Comment faire pour résoudre un syst non linéaire ?
-Forcer dérivée à gauche
-Revoir équation w[N]
*/


// Librairies utilisées
#include <iostream> // contient cin, cout ...
#include <fstream> // permet de lire et écrire dans un fichier
#include <cmath> // contient des fonctions mathématiques usuelles
#include <sys/time.h>
using namespace std;
// ----


// Variables relatives aux calculs
const float		n=1.; // valeur de l'indice polytropique

const int 		N=100; // nombre de noeuds de la grille de calcul
const float		z_max=4.; // valeur maximale de z
const double 	h=z_max/double(N); // pas en z

const double 	critere_convergence=1.e-8; // critère de convergence entre 2 itérations

double 			q[N+1],z[N+1],w[N+1]; // Masse, rayon et densité adimensionnées
double 			w_exact[N+1]; // densitée adimensionnée exacte
// ----


// Définition des fichiers de sortie
ofstream resultats_comparaison_methodes("resultats_comparaison_methodes.dat");
// ----


// Définition des fonctions
double f(double X)
{
	return pow(X,2)+2.*X-3.;
}


double Df(double X)
{
	return 2.*X+2.;
}


double calcul_zeros_NR(double nombre_de_depart,int i,double tolerance)
{
	// Méthode de Newton-Raphson
	int steps=0;
	double X,Y=nombre_de_depart;
	do	{
		steps++;
		if (steps%2000000==0)
		{
			cout << steps << "    " << Y << endl; // affichage du calcul
			// Y=nombre_de_depart;
		}
		
		// X_n+1 -> X_n
		// Y = X_n+1 = X_n  - f(X_n) / Df(X_n)
		
		X=Y; 
		Y=X-(f(X)/Df(X));

		} while ( abs(Y-X) > tolerance ); // test de tolérance

	return X;
}


double calcul_zeros_dichotomie(double a, double b, int i, double tolerance)
{
	// Méthode de la dichotomie
	double A=a,B=b,C;
	int steps=0;
	
	if (abs(f(A))<tolerance)
	{
		return f(A);
	}
	if (abs(f(B))<tolerance)
	{
		return f(B);
	}
	if (f(A)*f(B)>0)
	{
		cout << "Pas de changement de signe !"<<endl;
		return NULL;
	}
	while(true)
	{
		steps++;
		C=(A+B)/2.;
		// cout << steps << "	" << A << "	" << B << "	" << C << endl ;
		if (abs(f(C))<tolerance or steps==10000)
		{
			// cout << "1er if"<<endl;
			return C;
		}
		else
		{
			if (f(A)*f(C)>0.)
			{
				// cout << "2eme if" << endl;
				A=C;
				// getchar();
			}
			else
			{
				// cout << "else else" << endl;
				B=C;
				// getchar();
			}
		}
	}
}
// ----


int main()
{
	// Affichage d'informations sur le calcul
	
	// ----
	
	// Définition de la précision et du format des données
	cout.precision(4); // Précision de l'affichage (4 chiffres)
	cout<<std::fixed; // affichage fixé à 4 chiffres
	// ----
	
	int N=100000;
	double NR[N],dichotomie[N],t_NR[N],t_dichotomie[N];
	
	t_NR[0]=clock();
	for (int i = 1; i <= N; i++) {
		NR[i]=calcul_zeros_NR(i,0,1e-6);
		t_NR[i]=clock()-t_NR[i-1];
	}
	
	t_dichotomie[0]=clock();
	for (int i = 1; i <= N; i++) {
		dichotomie[i]=calcul_zeros_dichotomie(0.,i,0,1e-6);
		t_dichotomie[i]=clock()-t_dichotomie[i-1];
	}
	
	
	for (int i = 1; i <= N; i++) {
		resultats_comparaison_methodes << i << "	" << t_NR[i] << "	" << t_dichotomie[i] << endl;
	}
}
