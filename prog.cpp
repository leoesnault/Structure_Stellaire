/*
Programme de calcul de structure stellaire permettant de résoudre l'équation de Lane-Emden

A faire :
-Forcer dérivée à gauche
-Revoir équation w[N]
*/


// Librairies utilisées
#include <iostream> // contient cin, cout ...
#include <fstream> // permet de lire et écrire dans un fichier
#include <cmath> // contient des fonctions mathématiques usuelles
using namespace std;
// ----


// Variables relatives aux calculs
const float		n=1.; // valeur de l'indice polytropique

const int 		N=100; // nombre de noeuds de la grille de calcul
const float		z_max=4.; // valeur maximale de z
const double 	h=z_max/double(N); // pas en z

const double 	critere_convergence=1.e-10; // critère de convergence entre 2 itérations

double 			q[N+1],z[N+1],w[N+1]; // Masse, rayon et densité adimensionnées
double 			w_exact[N+1]; // densitée adimensionnée exacte
double 			w_prec[N+1]; // Sauvegarde de la valeur précédente de w
// ----


// Définition des fichiers de sortie
ofstream resultats("resultats.dat");
ofstream resultats_variables_physiques("resultats_variables_physiques.dat");
ofstream resultats_temp("resultats_temp.dat");
// ----


// Définition des fonctions
double calcul_zeros(double nombre_de_depart,int i,double tolerance,int nombre_iterations_max)
{
	// Méthode de Newton-Raphson
	double second_membre=w_prec[i+1]*((h/z[i])-1.) + w_prec[i-1]*(-(h/z[i])-1.);
	
	int steps=0;
	double X,Y=nombre_de_depart;
	do	{
		steps++;
		// cout << steps << "    " << Y << endl; // affichage du calcul
		
		// X_n+1 -> X_n
		// Y = X_n+1 = X_n  - f(X_n) / Df(X_n)
		
		X=Y; 
		Y=X-(pow(h,2)*pow(X,n)-2.*X-second_membre)/(n*pow(h,2)*pow(X,n-1)-2.);
		
		if (steps>nombre_iterations_max) // si le nombre d'itérations maximal est dépassé, afficher un message d'errreur et sortir
			{
			cout << "problème de convergence, nombre d'itérations autorisées dépassé"<<endl;
			break;
			}

		} while ( abs(Y-X) > tolerance ); // test de tolérance

	return X;
}


void initialisation_w()
{
	for (int i = 0; i <= N; i++) // initialisation w quadratique
	{
		w[i]=1.-(1./10.)*pow(z[i],2);
	}
}


void calcul_w()
{
	w[0]=1.; // Condition au centre de w
		
	bool convergence=false; // Booléen de convergence pour la boucle while
	
	int steps=0; // Nombre de pas de calcul avant convergence. Utile pour afficher tout les X pas
	
	while (convergence==false)
	{
		steps++;
		
		for (int i = 0; i <= N; i++)
		{
			w_prec[i]=w[i]; // Sauvegarde de w dans w_prec
		}
		
		w[1]=1.;//(1./4.)*(3.*w_prec[0]-w_prec[2]); // Dérivée nulle à gauche. OK???
		
		convergence=true;
		
		for (int i = 2; i <= N; i++)
		{
			// Calcul de w[i] pour n=1 !! Avec schéma excentré à gauche
			// w[i]=(1./(pow(h,2)-2.))*(w_prec[i+1]*((-h/z[i])-1.) + w_prec[i-1]*((h/z[i])-1.));
			w[i]=(1./(1.+(3.*h/z[i])+pow(h,2)))*(w_prec[i-2]*((-h/z[i])-1.)+w_prec[i-1]*(4.*(h/z[i])+2.));
			// ---
			
			// w[i]=calcul_zeros(w_prec[i],i,critere_convergence,1e3);
			
			if (abs(w_prec[i]-w[i])<critere_convergence) // A simplifier ?
			{
				convergence=convergence && true; // convergence==true si tout les points de w convergent
			}
			else
			{
				convergence=convergence && false; // Si un point ne converge pas, convergence==false
			}
		}
		
		if (steps%20==0 or steps==1) // Affichage/Écriture pour le 1er pas puis tout les X pas
		{
			cout << steps << "	" << w[int(N/2)] << endl; // Affichage du pas et d'une valeur arbitraire de w
			
			for (int i = 0; i <= N; i++)
			{
				resultats_temp
				<< z[i] << "		"
				<< w[i] << "		"
				<< w_exact[i] << endl; // Écriture des résultats temporaires
			}
		}
		
		// Pour n=1 :
		// w[N]=(1./(1.+(3.*h/z[N])+pow(h,2)))*(w_prec[N-2]*((-h/z[N])-1.)+w_prec[N-1]*(4.*(h/z[N])+2.));
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
		w_exact[0]=1.; // Forcage de w_exact[0], car sinon pb limite
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
		q[i]=(-1./z[i])*((-w[i-1]+w[i+1])/2.*h)*pow(z[i],3);
	}
	
	q[N]=(-1./z[N])*((w[N-2]-4.*w[N-1]+3.*w[N])/2.*h)*pow(z[N],3);
}
// ----


int main()
{
	// Affichage d'informations sur le calcul
	
	// ----
	
	
	// Définition de la précision et du format des données
	cout.precision(4); // Précision de l'affichage (4 chiffres)
	cout<<std::fixed; // affichage fixé à 4 chiffres
	resultats.precision(7); // Précision de l'écriture dans resultats
	resultats<<std::scientific; // Nombres écrits en notation scientifique
	resultats_variables_physiques.precision(7);
	resultats_variables_physiques<<std::scientific;
	// ----
	
	
	// Résolution et écriture
	calcul_z();
	initialisation_w();
	
	if(n!=0 and n!=1 and n!=5)
	{
		calcul_w();
		calcul_q();

		for (unsigned int i = 0; i <= N; i += 1)
		{
			resultats
			<< z[i] << "		"
			<< w[i] << "		"
			<< q[i] << endl;

			// resultats_variables_physiques
			// << z[i]/A << "		"
			// << pow(w[i],n)*rho_c << "		"
			// << K*pow(pow(w[i],n)*rho_c,float(n+1)/float(n)) << "		"
			// << q[i]*M << endl;
		}
	}
	else
	{
		calcul_w_exact();
		calcul_w();
		calcul_q();

		for (unsigned int i = 0; i <= N; i += 1)
		{
			resultats
			<< z[i] << "		"
			<< w[i] << "		"
			<< w_exact[i] << "		"
			<< q[i] << endl;

			// resultats_variables_physiques
			// << z[i]/A << "		"
			// << K*pow(pow(w[i],n)*rho_c,float(n+1)/float(n)) << "		"
			// << K*pow(pow(w_exact[i],n)*rho_c,float(n+1)/float(n)) << "		"
			// << pow(w[i],n)*rho_c << "		"
			// << pow(w_exact[i],n)*rho_c << "		"
			// << q[i]*M << endl;
		}
	}
	// ---
}
