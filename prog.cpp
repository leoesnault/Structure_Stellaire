/*
Programme de calcul de structure stellaire permettant de résoudre l'équation de Lane-Emden
*/


// Librairies utilisées
#include <iostream> // contient cin, cout ...
#include <fstream> // permet de lire et écrire dans un fichier
#include <cmath> // contient des fonctions mathématiques usuelles
using namespace std;
// ----


// Variables relatives aux calculs
double			n=1.; // valeur de l'indice polytropique

const int 		N=2000; // nombre de noeuds de la grille de calcul
const float		z_max=40.; // valeur maximale de z
const double 	h=z_max/N; // pas en z

const double 	critere_convergence=1.e-10; // critère de convergence entre 2 itérations

double 			q[N+1],z[N+1],w[N+1]; // Masse, rayon et densitée adimensionnées
double 			w_exact[N+1]; // densitée adimensionnée exacte

bool 			error_status=false; // initialisation de la variable d'erreur
// ----


// Définition des fichiers de sortie
ofstream resultats("resultats.dat");
// ----


// Définition des fonctions
double f(double X, int i) // fonction pour le calcul de racine dans les 2 méthodes
{
	// Schéma excentré à gauche
	return pow(h,2)*pow(X,n)+(1.+(3.*h/z[i]))*X-(w[i-2]*((-h/z[i])-1.)+w[i-1]*(4.*(h/z[i])+2.));
}


double Df(double X, int i) // dérivée pour le calcul de racine dans la méthode de Newton
{
	// Schéma excentré à gauche
	return n*pow(h,2)*pow(X,n-1)+(1.+(3.*h/z[i]));
}


double calcul_zeros_NR(double nombre_de_depart,int i,double tolerance,int nombre_iterations_max)
{
	// Méthode de Newton-Raphson
	int etape=0;
	double X,Y=nombre_de_depart;
	do	{
		etape++;
		if (etape>nombre_iterations_max)
		{
			cout << "Nombre d'itérations maximum dépassées." << endl;
			error_status=true;
			return NULL; // sortie de fonction
		}
		
		X=Y; 
		Y=X-(f(X,i)/Df(X,i));

		} while ( abs(Y-X) > tolerance ); // test de tolérance

	return X;
}


double calcul_zeros_dichotomie(double a, double b, int i, double tolerance)
{
	// Méthode de la dichotomie
	double A=a,B=b,C; // copie des variables d'entrée et déclaration de C
	int etape=0; // initialisation du nombre d'étapes
	
	if (f(A,i)*f(B,i)>0)
	{
		cout << "Pas de changement de signe !"<<endl;
		error_status=true;
		return NULL; // sortie de fonction
	}
	if (abs(f(A,i))<tolerance)
	{
		return f(A,i);
	}
	if (abs(f(B,i))<tolerance)
	{
		return f(B,i);
	}
	
	while(true)
	{
		etape++;
		C=(A+B)/2.;
		if (abs(f(C,i))<tolerance)
		{
			return C;
		}
		else
		{
			if (f(A,i)*f(C,i)>0.)
			{
				A=C;
			}
			else
			{
				B=C;
			}
		}
	}
}


void calcul_w()
{
	w[0]=1.; // Condition au centre de w
	w[1]=1./(1.+(pow(h,2)/6.));
	
	for (int i = 2 ; i<=N ; i++)
	{
		// w[i]=calcul_zeros_dichotomie(w[i-1]-0.01,w[i-1]+0.01,i,critere_convergence);
		w[i]=calcul_zeros_NR(w[i-1],i,critere_convergence,1e6);
		
		if (error_status) // sortir si erreur
		{
			break;
		}
	}

}


void calcul_w_exact()
{
	if (n==0)
	{
		for (int i = 0; i <= N; i++)
		{
			w_exact[i] = 1.-pow(z[i],2)/6.;
		}
	}
	if (n==1)
	{
		w_exact[0]=1.; // w_exact[0] forcé à 1 car sinon pb limite
		for (int i = 1; i <= N; i++)
		{
			w_exact[i] = sin(z[i])/z[i];
		}
	}
	if (n==5)
	{
		for (int i = 0; i <= N; i++)
		{
			w_exact[i] = 1./sqrt(1.+pow(z[i],2)/3.);
		}
	}
}


void calcul_z()
{
	z[0]=0.;
	
	for (int i = 1; i <= N; i++)
	{
		z[i]=i*h;
	}
}


void calcul_q()
{
	q[0]=0.;
		
	for (int i = 1; i < N; i++)
	{
		q[i]=(-pow(z[i],2))*((-w[i-1]+w[i+1])/2.*h);
	}
}
// ----


int main() // Début du programme principal
{
	// Affichage d'informations sur le calcul
	cout << "##############################################################################"<<endl
		<<  "# Éxecution du programme de calcul des solutions de l'équation de Lane-Emden #" << endl
		<<  "##############################################################################"<<endl << endl
		<<  "Indice polytropique  : n = " << n << endl << endl
		<<  "Valeur maximale de : z = " << z_max << endl << endl
		<<  "Nombre de points : N = " << N << endl << endl
		<<  "Pas de calcul : h = " << h << endl << endl
		<<  "Critère de convergence : critere_convergence = " << critere_convergence << endl << endl
		<<  "##############################################################################"<<endl << endl;
	// ----
	
	
	// Définition de la précision et du format des données
	cout.precision(4); // Précision de l'affichage (4 chiffres)
	cout<<std::fixed; // affichage fixé à 4 chiffres
	resultats.precision(7); // Précision de l'écriture dans resultats
	resultats<<std::scientific; // Nombres écrits en notation scientifique
	// ----
	
	// Résolution et écriture
	calcul_z();
	calcul_w_exact();
	calcul_w();
	calcul_q();

	if (error_status==false)
	{
		if(n!=0 and n!=1 and n!=5)
		{
			for (unsigned int i = 0; i <= N; i += 1)
			{
				resultats
				<< z[i] << "		"
				<< w[i] << "		"
				<< q[i] << endl;
			}
		}
		else
		{
			for (unsigned int i = 0; i <= N; i += 1)
			{
				resultats
				<< z[i] << "		"
				<< w[i] << "		"
				<< w_exact[i] << "		"
				<< q[i] << endl;
			}
		}
		
		cout << "Programme executé avec succès !"<< endl << endl;
	}
	else
	{
		cout << "Erreur ! Programme non executé."<< endl << endl;
	}
	// ---
}
