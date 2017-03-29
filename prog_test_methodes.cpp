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
const int N=100000;
int steps_NR[N],steps_dichotomie[N];
double t_NR[N],t_dichotomie[N];
double NR,dichotomie;
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
	steps_NR[i]=0;
	double X,Y=nombre_de_depart;
	do	{
		steps_NR[i]++;
		// if (steps_NR%2000000==0)
		// {
		// 	cout << steps_NR[i] << "    " << Y << endl; // affichage du calcul
		// 	// Y=nombre_de_depart;
		// }

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
	steps_dichotomie[i]=0;
	double A=a,B=b,C;

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
		steps_dichotomie[i]++;
		C=(A+B)/2.;
		// cout << steps << "	" << A << "	" << B << "	" << C << endl ;
		if (abs(f(C))<tolerance)
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
	double i_by=20.;

	t_NR[0]=clock();
	steps_NR[0]=0;
	for (int i = 1; i <= N; i++) {
		NR=calcul_zeros_NR(i/i_by,i,1e-6);
		t_NR[i]=clock()-t_NR[i-1];
	}

	steps_dichotomie[0]=0;
	t_dichotomie[0]=clock();
	for (int i = 1; i <= N; i++) {
		dichotomie=calcul_zeros_dichotomie(0.,1.+i/i_by,i,1e-6);
		t_dichotomie[i]=clock()-t_dichotomie[i-1];
	}


	for (int i = 1; i <= N; i++) {
		resultats_comparaison_methodes
		<< i/i_by << "	" << t_NR[i] << "	" << steps_NR[i] << "	"
		<< t_dichotomie[i] << "	" << steps_dichotomie <<endl;
	}
}
