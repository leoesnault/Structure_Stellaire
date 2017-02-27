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

const int 		N=200; // nombre de noeuds de la grille de calcul
const float		z_max=4.; // valeur maximale de z
const double 	h=z_max/double(N); // pas en z

const double 	critere_convergence=1.e-10; // critère de convergence entre 2 itérations

double 			q[N+1],z[N+1],w[N+1]; // Masse, rayon et densité adimensionnées
double 			w_exact[N+1]; // densitée adimensionnée exacte
double 			w_prec[N+1]; // Sauvegarde de la valeur précédente de w
// ----


// Définition des fichiers de sortie
ofstream resultats("resultats.dat");
ofstream resultats_temp("resultats_temp.dat");
// ----


// Définition des fonctions
double f(double X, int i)
{
	return pow(h,2)*pow(X,n)-(1.+(3.*h/z[i]))*X-(w_prec[i-2]*((-h/z[i])-1.)+w_prec[i-1]*(4.*(h/z[i])+2.));
}


double Df(double X, int i)
{
	return n*pow(h,2)*pow(X,n-1)-(1.+(3.*h/z[i]));
}


double calcul_zeros_NR(double nombre_de_depart,int i,double tolerance,int nombre_iterations_max)
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
		Y=X-(f(X,i)/Df(X,i));

		} while ( abs(Y-X) > tolerance ); // test de tolérance

	return X;
}


double calcul_zeros_dichotomie(double a, double b, int i, double tolerance)
{
	// Méthode de la dichotomie
	double A=a,B=b,C;
	int steps=0;
	while(true)
	{
		steps++;
		C=(A+B)/2.;
		cout << steps << "	" << A << "	" << B << "	" << C << endl ;
		if (abs(f(C,i))<tolerance)
		{
			cout << "1er if"<<endl;
			return C;
			break;
		}
		else
		{
			if (f(A,i)*f(B,i)<0.)
			{
				cout << "2eme if" << endl;
				B=C;
				getchar();
			}
			else
			{
				cout << "else else" << endl;
				A=C;
				// getchar();
			}
		}
	}
}


void initialisation_w()
{
	for (int i = 0; i <= N; i++) // initialisation w quadratique
	{
		w[i]=1.;
		/*
		1.-(1./10.)*pow(z[i],2);
		
		*/
	}
}


void calcul_w()
{		
	bool convergence=false; // Booléen de convergence pour la boucle while
	
	int steps=0; // Nombre de pas de calcul avant convergence. Utile pour afficher tout les X pas
	
	while (convergence==false)
	{
		steps++;
		
		// Sauvegarde de w dans w_prec
		for (int i = 0; i <= N; i++)
		{
			w_prec[i]=w[i]; // Sauvegarde de w dans w_prec
		}
		// ----
		
		
		// Calcul de w
		
		w[0]=1.; // Condition au centre de w
		w[1]=1.;//(1./4.)*(3.*w_prec[0]-w_prec[2]); // Dérivée nulle à gauche. OK???
		
// Schéma centré, partant du centre, avec borne à 0 à droite
		// for (int i = 2; i < N; i++)
		// {
		// 	w[i]=(1./(pow(h,2)-2.))*(w_prec[i+1]*((h/z[i])-1.) + w_prec[i-1]*(-(h/z[i])-1.));
		// }
		// w[N]=-0.;
		
// Schéma excentré à gauche, partant du centre (Fonctionne !)
		for (int i = 2 ; i<=N ; i++)
		{
			w[i]=(1./(1.+(3.*h/z[i])+pow(h,2)))*(w_prec[i-2]*((-h/z[i])-1.)+w_prec[i-1]*(4.*(h/z[i])+2.));
		}
		
// Schéma excentré à gauche, partant du bord (Fonctionne !)
		// for (int i = N ; i > 1 ; i--)
		// {
		// 	w[i]=(1./(1.+(3.*h/z[i])+pow(h,2)))*(w_prec[i-2]*((-h/z[i])-1.)+w_prec[i-1]*(4.*(h/z[i])+2.));
		// }
		
// Les deux schémas qui se rejoignent à un point, partant du centre
		// for (int i = 2; i <= int(float(N)/2.); i++)
		// {
		// 	w[i]=(1./(pow(h,2)-2.))*(w_prec[i+1]*((h/z[i])-1.) + w_prec[i-1]*(-(h/z[i])-1.));
		// }
		// 
		// for (int i = int(float(N)/2.) ; i <= N; i++)
		// {
		// 	w[i]=(1./(1.+(3.*h/z[i])+pow(h,2)))*(w_prec[i-2]*((-h/z[i])-1.)+w_prec[i-1]*(4.*(h/z[i])+2.));
		// }
		
		// ----
		
		
		// Test de convergence
		convergence=true;
		
		for (int i = 0; i <= N; i++)
		{
			if (abs(w_prec[i]-w[i])<critere_convergence)
			{
				convergence=convergence && true; // convergence==true si tout les points de w convergent
			}
			else
			{
				convergence=convergence && false; // Si un point ne converge pas, convergence==false
			}
		}
		// ----
		
		
		// Affichage temporaire
		if (steps%20000==0 or steps==1) // Affichage/Écriture pour le 1er pas puis tout les X pas
		{
			cout << steps << "	" << w[int(float(N)/2.)] << endl; // Affichage du pas et d'une valeur arbitraire de w
			
			for (int i = 0; i <= N; i++)
			{
				resultats_temp
				<< z[i] << "		"
				<< w[i] << "		"
				<< w_exact[i] << endl; // Écriture des résultats temporaires
			}
		}
		// ----
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
		}
	}
	// ---
}
