/*
Programme de calcul de structure stellaire permettant de résoudre l'équation de Lane-Emden

A faire :
-Forcer dérivée au centre -> Forcer w[1] ou w[2] ?
-Verifier calcul w -> OK ?
-Utiliser w[j] ou w_prec[j] dans le calcul ?
-Calculer en fonction de la parité ?
-Raccrocher schéma centré et excentré à gauche pour pouvoir calculer w[N]
-Trouver critères pour NR et dichotomie -> w[i] et ±1000 a priori OK
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
const float		z_max=2.; // valeur maximale de z
const double 	h=z_max/double(N); // pas en z

const double 	critere_convergence=1.e-10; // critère de convergence entre 2 itérations

double 			q[N+1],z[N+1],w[N+1]; // Masse, rayon et densité adimensionnées
double 			w_exact[N+1]; // densitée adimensionnée exacte
double 			w_prec[N+1]; // Sauvegarde de la valeur précédente de w

bool 			error_status=false;
// ----


// Définition des fichiers de sortie
ofstream resultats("resultats.dat");
ofstream resultats_temp("resultats_temp.dat");
// ----


// Définition des fonctions
double f(double X, int i)
{
	// Schéma excentré à gauche
	return pow(h,2)*pow(X,n)+(1.+(3.*h/z[i]))*X-(w_prec[i-2]*((-h/z[i])-1.)+w_prec[i-1]*(4.*(h/z[i])+2.));
	
	// Schéma centré
	// return pow(h,2)*pow(X,n)-2.*X-((w_prec[i+1]*((-h/z[i])-1.) + w_prec[i-1]*((h/z[i])-1.)));
}


double Df(double X, int i)
{
	// Schéma excentré à gauche
	return n*pow(h,2)*pow(X,n-1)+(1.+(3.*h/z[i]));
	
	// Schéma centré
	// return n*pow(h,2)*pow(X,n-1)-2.;
}


double calcul_zeros_NR(double nombre_de_depart,int i,double tolerance,int nombre_iterations_max)
{
	// Méthode de Newton-Raphson
	int steps=0;
	double X,Y=nombre_de_depart;
	do	{
		steps++;
		if (steps>nombre_iterations_max)
		{
			cout << "Nombre d'itérations maximum dépassées." << endl;
			error_status=true;
			return NULL; // return foireux (sortie de fonction)
		}
		
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
	
	if (f(A,i)*f(B,i)>0)
	{
		cout << "Pas de changement de signe !"<<endl;
		error_status=true;
		return NULL; // return foireux (sortie de fonction)
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
		steps++;
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


void initialisation_w()
{
	for (int i = 0; i <= N; i++) // initialisation w quadratique
	{
		w[i]=1.-pow(z[i],2)/6.;
		/*
		1.-(1./10.)*pow(z[i],2);
		
		*/
	}
}


void calcul_w()
{		
	bool convergence=false; // Booléen de convergence pour la boucle while
	
	int steps=0; // Nombre de pas de calcul effectués. Utile pour afficher tout les X pas
	
	cout << "steps" << "	" << "w[N/2]" << endl;
	
	while (convergence==false and error_status==false)
	{
		steps++;
		
		// Sauvegarde de w dans w_prec
		for (int i = 0; i <= N; i++)
		{
			w_prec[i]=w[i];
		}
		// ----
		
		
		// Calcul de w
		w[0]=1.; // Condition au centre de w
		w[1]=1./(1.+(pow(h,2)/6.));
		// w[2]=-3.*w[0]+4.*w[1]; // Ici on force w[2]
		
	// Schéma centré, partant du centre, calcul tout les pas pairs, puis impairs 
		// w[N]=(1./(1.+(3.*h/z[N])+pow(h,2)))*(w[N-2]*((-h/z[N])-1.)+w[N-1]*(4.*(h/z[N])+2.));
		w[N] = 0.454972; // Condition au bord forcée à -0,19 (pour commencer)
		
		// for (int i = 4; i < N; i+=2)
		// {
		// 	w[i]=(1./(pow(h,2)-2.))*(w_prec[i+1]*((-h/z[i])-1.)+w_prec[i-1]*((h/z[i])-1.));
		// }
		// for (int i = 1; i < N-1; i+=2)
		// {
		// 	w[i]=(1./(pow(h,2)-2.))*(w_prec[i+1]*((-h/z[i])-1.)+w_prec[i-1]*((h/z[i])-1.));
		// }
		// 
		
		for (int i = 2; i < N; i++)
		{
			w[i]=(1./(pow(h,2)-2.))*(-w[i+1]*((h/z[i])+1.)+w[i-1]*((h/z[i])-1.));
		}
		// 
	// Schéma centré, partant du centre, calcul sans tenir compte de la parité
		// w[N]=(1./(1.+(3.*h/z[N])+pow(h,2)))*(w[N-2]*((-h/z[N])-1.)+w[N-1]*(4.*(h/z[N])+2.));
		// w[N]=-0.19; // Condition au bord forcée à -0,19 (pour commencer)
		
		// for (int i = 1; i < N; i+=1)
		// {
		// 	w[i]=(1./(pow(h,2)-2.))*(w_prec[i+1]*((-h/z[i])-1.)+w_prec[i-1]*((h/z[i])-1.));
		// }
		
	// Schéma excentré à gauche, partant du centre
		// for (int i = 2 ; i<=N ; i++)
		// {
		// 	w[i]=(1./(1.+(3.*h/z[i])+pow(h,2)))*(w_prec[i-2]*((-h/z[i])-1.)+w_prec[i-1]*(4.*(h/z[i])+2.));
		// 	// w[i]=calcul_zeros_dichotomie(-1e2,1e2,i,1e-6);
		// 	// w[i]=calcul_zeros_NR(w_prec[i],i,1e-6,1e7);
		// }
		
	// Les deux schémas qui se rejoignent au point "borne", partant du centre, calcul avec parité
		// int borne=4;
		
		// for (int i = 4; i < borne; i+=2)
		// {
		// 	w[i]=(1./(pow(h,2)-2.))*(w_prec[i+1]*((-h/z[i])-1.)+w_prec[i-1]*((h/z[i])-1.));
		// }
		// for (int i = 1; i < borne; i+=2)
		// {
		// 	w[i]=(1./(pow(h,2)-2.))*(w_prec[i+1]*((-h/z[i])-1.)+w_prec[i-1]*((h/z[i])-1.));
		// }
		
		// for (int i = borne; i <= N; i++)
		// {
		// 	w[i]=(1./(1.+(3.*h/z[i])+pow(h,2)))*(w_prec[i-2]*((-h/z[i])-1.)+w_prec[i-1]*(4.*(h/z[i])+2.));
		// }		
		
	// Les deux schémas qui se rejoignent au point "borne", partant du centre, calcul sans parité
		// int borne=4;

		// for (int i = 2; i <= borne; i++)
		// {
		// 	w[i]=(1./(pow(h,2)-2.))*(w_prec[i+1]*((-h/z[i])-1.)+w_prec[i-1]*((h/z[i])-1.));
		// }
		
		// for (int i = borne; i <= N; i++)
		// {
		// 	w[i]=(1./(1.+(3.*h/z[i])+pow(h,2)))*(w_prec[i-2]*((-h/z[i])-1.)+w_prec[i-1]*(4.*(h/z[i])+2.));
		// }
		
	// Synthaxe du calcul de zéros (à laisser en commentaire)
		// w[i]=calcul_zeros_NR(w[i],i,1e-6,1e6);
		// w[i]=calcul_zeros_dichotomie(-1e2,1e2,i,1e-6)
		
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
		if (steps%10000==0 or steps==1) // Affichage/Écriture pour le 1er pas puis tout les X pas
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
		q[i]=(-1./z[i])*((-w[i-1]+w[i+1])/2.*h)*pow(z[i],3);
	}
	
	q[N]=(-1./z[N])*((w[N-2]-4.*w[N-1]+3.*w[N])/2.*h)*pow(z[N],3); // A re-vérif une fois que calcul_w OK
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
	calcul_w_exact();
	initialisation_w();
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
	}
	else
	{
		cout << "Erreur ! Programme non executé."<<endl;
	}
	// ---
}
