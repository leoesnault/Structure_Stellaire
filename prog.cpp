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
#include <vector> // permet de déclarer des tableaux dynamiques
using namespace std;
// ----




// Données physiques
const double 	G=6.6741e-11,
							pi=3.1415; // constantes physiques et mathématiques
double 				M=1.9891e30,
							R=6.9634e8,
							n=1.,
							K=2.e16; // Masse totale, rayon, indice polytropique et constante polytropique(a trouver)
//float u=(d ln(M))/(d ln(r)),v=-(d ln(P))/(d ln(r)); // variables de Milne
// ----


// Variables relatives aux calculs
double 				P_c=(2.*G/pi*pow(R,4)),
							rho_c=pow((P_c/K),n/(n+1)); // estimation pression et densité au centre
double 				A=sqrt(4.*pi*G/(float(n+1)*K*pow(rho_c,(1-n)/n)));

const int 		N=100; // nombre de noeuds de la grille de calcul
const double 	h=R; // pas de masse

double 				q[N+1],z[N+1],w[N+1];
double 				w_exact[N+1],w_GS[N+1],w_prec[N+1];

float 				omega=1.;
double 				a[N+1],b[N+1],c[N+1],B[N+1];
float 				critere_convergence=0.01;
// ----


// Définition des fonctions
//double calcul_Gauss_Seidel(vector<float> x,float critere_convergence)
//{
//	do
//	{
//		for (unsigned int i = 0; i <= N; i += 1)
//		{
//			double sum=0.;
//
//			for (unsigned int j = 0; j <= N; j += 1)
//			{
//				if (j!=i)
//				{
//					sum = sum + a[i][j]*x[j];
//				}
//			}
//			x_GS[i]=(b[i]-sum)/aii;
//		}
//
//	} while (abs(x_GS[i] - x_prec)>critere_convergence)
//
//	return x_GS;
//
//}


//double calcul_Relaxation(vector<float> x, float critere_convergence)
//{
//	do
//	{
//		for (unsigned int i = 1; i <= N; i += 1)
//		{
//			x[i]=omega*x_GS[i]+(1.-omega)*x[i];
//		}
//	} while(abs(x_GS[i] - x_prec)>critere_convergence)
//
//	return x;
//
//}


void calcul_solution_exacte(int i)
{
	if (n==0)
	{
		w_exact[i] = 1.-pow(A*(i/double(N))*h,2)/6.;
	}
	if (n==1)
	{
		w_exact[i] = sin(A*(i/double(N))*h)/A*(i/double(N))*h;
	}
	if (n==5)
	{
		w_exact[i] = 1./sqrt(1.+pow(A*(i/double(N))*h,2)/3.);
	}
}
// ----







int main()
{
	// Affichage d'informations sur le calcul
	cout << "Modèle polytropique de structure stellaire pour une étoile de rayon "<<R<<"m et de masse "<<M<<"kg."<<endl;
	cout <<"P_c = "<< P_c << "   rho_c = "<< rho_c << "   A = " << A << endl;
	// ----
	// Rho doit être de l'ordre de 1.50e5 kg.m^-3 au centre


	// Définition du fichier de sortie
	ofstream results("results.dat");
	// ----

	// Définition des conditions au centre et remplissage des vecteurs a, b, c
	q[0]=0.;
	z[0]=0.;
	w[0]=1.;

	a[0]=0.;//normalement inutile
	b[0]=1.;
	c[0]=-1.;

	a[N]=0.;
	b[N]=1.;
	c[N]=0.;//normalement inutile
	for (unsigned int i = 1; i < N; i += 1)
	{
		a[i]=-1./pow(h,2)-1./(2.*(i/double(N))*h*h);
		b[i]=2./pow(h,2);
		c[i]=-1./pow(h,2)+1./(2.*(i/double(N))*h*h);
	}
	// ----

	// Résolution
	int convergence_sur_tout_z;

		double sum=0.;
		do
		{
			convergence_sur_tout_z=0;

			for (unsigned int i = 0; i <= N; i += 1)
			{
				w_prec[i]=w_GS[i];

				sum = sum + a[i]*w_GS[i] + c[i]*w_GS[i];//a[i][j]*w[j];

				w_GS[i]=(B[i]-sum)/b[i];

				if (abs(w_GS[i]-w_prec[i])<critere_convergence)
				{
					convergence_sur_tout_z ++;
				}
			}

		} while (convergence_sur_tout_z<N);



		do
		{
			convergence_sur_tout_z=0;
			for (unsigned int i = 1; i <= N; i += 1)
			{
				w[i]=omega*w_GS[i]+(1.-omega)*w[i];

				if (abs(w_GS[i]-w_prec[i])<critere_convergence)
				{
					convergence_sur_tout_z ++;
				}
			}
		} while(convergence_sur_tout_z<N);


	for (unsigned int i = 0; i <= N; i += 1) // Besoin de boucler ? Ici boucle sur les pas d'espace
	{
		z[i]=i*h;
		q[i]=1.; // Attention ! a Modif !

		// Écrit r, m, rho, P pour le point considéré
		if(n!=0 and n!=1 and n!=5)
		{
			results
			<< z[i]/A << "	"
			<< q[i]*M << "	"
			<< pow(w[i],n)*rho_c << "	"
			<< K*pow(pow(w[i],n)*rho_c,float(n+1)/float(n)) << endl;
		}
		else
		{
			calcul_solution_exacte(i);
			results
			<< z[i]/A << "	"
			<< q[i]*M << "	"
			<< pow(w[i],n)*rho_c << "	"
			<< pow(w_exact[i],n)*rho_c << "	"
			<< K*pow(pow(w[i],n)*rho_c,float(n+1)/float(n)) << "	"
			<< K*pow(pow(w_exact[i],n)*rho_c,float(n+1)/float(n)) << endl;
		}
		// ----

	}
	// ---

}
