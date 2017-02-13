/*
Programme de calcul de structure stellaire, utilisant les hypothèses :
-Gaz autogravitant à l'équilibre
-Chimiquement homogène
-Sans rotation propre
-Équation d'état polytropique
-Solutions à une dimension
-

A faire :
-Trouver une valeur raisonnable de K. plus vers 1e7 ou 1e16 ou 1 ?
-Quelles données à entrer dans le programme ?
-Conditions en surface ?
-Modifier l'algo de résolution de w. Comment faire pour résoudre un syst non linéaire ?
- !!!! problème en z=1 !!!!
*/


// Librairies utilisées
#include <iostream> // contient cin, cout ...
#include <fstream> // permet de lire et écrire dans un fichier
#include <cmath> // contient des fonctions mathématiques usuelles
using namespace std;
// ----


// Données physiques
const double 	G=6.6741e-11,
				pi=3.1415; // constantes physiques et mathématiques
double 			M=1.9891e30,
				R=6.9634e8,
				n=1.,
				K=5e7;//e16; // Masse totale, rayon, indice polytropique et constante polytropique(a trouver)
// ----


// Variables relatives aux calculs
double 			P_c=(2.*G/pi*pow(R,4)),
				rho_c=pow((P_c/K),n/(n+1)); // estimation pression et densité au centre
double 			A=sqrt(4.*pi*G/(float(n+1)*K*pow(rho_c,(1-n)/n)));

const int 		N=100; // nombre de noeuds de la grille de calcul
const double 	h_r=R/N,h_z=A*h_r; // pas en r et z

double 			q[N+1],z[N+1],w[N+1];
double 			w_exact[N+1],w_GS[N+1],w_prec[N+1];

// float 			omega=1.;
// double 			a[N+1],b[N+1],c[N+1],B[N+1];
float 			critere_convergence=0.001;
// ----


// Définition des fonctions
void initialisation_w()
{
	// cout << "Initialisation : "<< endl;
	for (int i = 0; i <= N; i++) // initialisation w quadratique
	{
		w[i]=1.-(1./2.)*pow(i*h_z,1);
		// cout << w[i] << endl;
	}
}


// bool test_derivee_centrale_w()
// {
// 	if (-3.*w[1]+4.*w[2]-w[3]<critere_convergence)
// 	{
// 		return true;
// 	}
// 	else
// 	{
// 		return false;
// 	}
// }


// bool test_convergence_w(int i)
// {
// 	float terme_de_gauche=pow(h_z,2)*pow(w[i],n)-2.*w[i];
// 	float terme_de_droite=w[i+1]*((h_z/z[i])+1.) + w[i-1]*((h_z/z[i])-1.);
// 	
// 	if ( abs(terme_de_gauche-terme_de_droite)<critere_convergence )
// 	{
// 		return true;
// 	}
// 	else
// 	{
// 		return false;
// 	}
// }


void calcul_w()
{
	w[0]=1.;
	
	bool convergence=false;
	
	while (convergence==false)
	{
		for (int i = 0; i <= N; i++)
		{
			w_prec[i]=w[i];
		}
		
		convergence=true;
		
		for (int i = 1; i <= N; i++)
		{
			// "Forcage" de la dérivée nulle au centre
			// w[1]=(1./4.)*(3.*w[0]-w[2]);
			// ----
			
			/* Calcul de w[i] pour n=1 !! */
			w[i]=(1./(pow(h_z,2)-2.))*(w[i+1]*((h_z/z[i])-1.) + w[i-1]*(-(h_z/z[i])-1.));
			// w[i]=abs(w[i]);
			// cout<<w[i]<<endl;
			
			if (abs(w_prec[i]-w[i])<critere_convergence) // A simplifier ?
			{
				convergence=convergence && true;
			}
			else
			{
				convergence=convergence && false;
			}
		}
		// getchar();
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
		z[0]=1.;
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
	for (int i = 0; i <= N; i++)
	{
		z[i]=i*h_z;
	}
}


void calcul_q() // A MODIF ? Décentré ordre 2 ?
{
	q[0]=0.;
	for (int i = 1; i <= N; i++)
	{
		q[i]=-4.*pi*rho_c*(pow(z[i]/A,2)/A)*((w[i]-w[i-1])/h_z)*(1./M);// Schéma à gauche
	}
}
// ----


int main()
{
	// Affichage d'informations sur le calcul
	cout << "Modèle polytropique de structure stellaire pour une étoile de rayon "<<R<<"m et de masse "<<M<<"kg."<<endl;
	cout <<"P_c = "<< P_c << "   rho_c = "<< rho_c << "   A = " << A << endl;
	// ----


	// Définition des fichiers de sortie et de la précision
	ofstream resultats("resultats.dat");
	ofstream resultats_variables_physiques("resultats_variables_physiques.dat");

	cout.precision(4);
	cout<<std::fixed;
	resultats.precision(7);
	resultats<<std::scientific;
	resultats_variables_physiques.precision(7);
	resultats_variables_physiques<<std::scientific;
	// ----


	// Remplissage des vecteurs a, b, c. A REVOIR (Conditions au centre et au bord)
/*	a[0]=0.;//normalement inutile
	b[0]=1.;
	c[0]=0.;

	a[N]=0.;
	b[N]=1.;
	c[N]=0.;//normalement inutile
	for (unsigned int i = 1; i < N; i += 1)
	{
		a[i]=-1./pow(h_z,2)-1./(2.*i*h_z*h_z);
		b[i]=2./pow(h_z,2);
		c[i]=-1./pow(h_z,2)+1./(2.*i*h_z*h_z);
	}

	for (int i = 0; i <= N; i++)
	{
		B[i]=0.; // A modif, second membre
	}
*/
	// ----


	// Résolution et écriture
	initialisation_w();
	
	if(n!=0 and n!=1 and n!=5)
	{
		// resultats
		// <<"z"<<"	"<<"w"<<"	"<<"q"<<endl;
		// resultats_variables_physiques
		// <<"r"<<"	"<<"rho"<<"	"<<"P"<<"	"<<"m"<<endl;

		calcul_z();
		calcul_w();
		calcul_q();

		for (unsigned int i = 0; i <= N; i += 1)
		{
			resultats
			<< z[i] << "		"
			<< w[i] << "		"
			<< q[i] << endl;

			resultats_variables_physiques
			<< z[i]/A << "		"
			<< pow(w[i],n)*rho_c << "		"
			<< K*pow(pow(w[i],n)*rho_c,float(n+1)/float(n)) << "		"
			<< q[i]*M << endl;
		}
	}
	else
	{
		// resultats
		// <<"z"<<"	"<<"w"<<"	"<<"w_exact"<<"	"<<"q"<<endl;
		// resultats_variables_physiques
		// <<"r"<<"	"<<"rho"<<"	"<<"rho_exact"<<"	"<<"P"<<"	"<<"P_exact"<<"	"<<"m"<<endl;
		calcul_z();
		calcul_w();
		calcul_w_exact();
		calcul_q();

		for (unsigned int i = 0; i <= N; i += 1)
		{
			resultats
			<< z[i] << "		"
			<< w[i] << "		"
			<< w_exact[i] << "		"
			<< q[i] << endl;

			resultats_variables_physiques
			<< z[i]/A << "		"
			<< K*pow(pow(w[i],n)*rho_c,float(n+1)/float(n)) << "		"
			<< K*pow(pow(w_exact[i],n)*rho_c,float(n+1)/float(n)) << "		"
			<< pow(w[i],n)*rho_c << "		"
			<< pow(w_exact[i],n)*rho_c << "		"
			<< q[i]*M << endl;
		}
	}
	// ---

}
