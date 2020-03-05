#include "Vecteur.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
	Vecteur vect1;
	Vecteur vect2;
	Vecteur vect3;

//SET COORDONNEES 
	//v1 = (1.0, 2.0, -0.1)
	vect1.augmente(1.0); vect1.augmente(0.0); vect1.augmente(-0.1);
	vect1.set_coord(1, 2.0);

    // v2 = (2.6, 3.5,  4.1)
	vect2.augmente(2.6); vect2.augmente(3.5); vect2.augmente(4.1);
	vect3 = vect1;
//AFFICHE
	cout << "Vecteur 1 : ";
	vect1.affiche();
	cout << endl;

	cout << "Vecteur 2 : ";
	vect2.affiche();
	cout << endl;
//COMPARAISON
	cout << "Le vecteur 1 est ";
	if (vect1.compare(vect2)) {
		cout << "égal au";
	} else {
		cout << "différent du";
	}
	cout << " vecteur 2," << endl << "et est ";
	if (not vect1.compare(vect3)) {
		cout << "différent du";
	} else {
		cout << "égal au";
	}
	cout << " vecteur 3." << endl;
//ADDITION v1 + v2 = ( 3.6 , 5.5, 4.0)
	Vecteur vect4;
	vect4 = vect1.addition(vect2);
	cout << "vect1+vect2 : ";
	vect4.affiche();
	cout << endl;
//SOUSTRACTION v1 - v2 = ( -1.6, -1.5, -4.2)
	vect4 = vect1.soustraction(vect2);
	cout << "vect1-vect2 : ";
	vect4.affiche(); 
	cout << endl;
//MULTIPLICATION PAR UN SCALAIRE v1*2 = ( 2.0 , 4.0 , -0.2 )
	vect4 = vect1.mult(2);
	cout << "vect1*2 :";
	vect4.affiche();
//PRODUIT SCALAIRE v1.v1 = 5.01
	double x;
	try {
	x = vect1.prod_scal(vect1);
	cout << "prod scalaire v1.v1 : " << x << endl;
	}
	catch (string& s) {
		if (s=="DIMENSIONS!") {
			cerr << "erreur opération entre deux vecteurs de dimensions différentes" << endl;
		}
	}
//PRODUIT VECTORIEL v1Xv2 = ( 8.55 , -4.36 , -1.7 )
	vect4 = vect1.prod_vect(vect2);
	cout << "produit vectoriel v1xv2 : ";
	vect4.affiche();
// norme2 v1 = 5.01
	cout << "norme au carre de v1 : " << vect1.norme2() << endl;
//norme v2 ~ 2.238
	cout << "norme de v1 : " << vect1.norme() << endl;
// Vecteur unitaire de v1 ~ ( 0.45 , 0.89 , -0.04)
	vect4 = vect1.unitaire();
	cout << "Vecteur unitaire de v1 : ";
	vect5.affiche();
	cout << " de norme : " << vect5.norme() << endl;
////TEST EXCEPTIONS
	Vecteur vect6({1.5,2});
	cout << "vect6 : ";
	vect6.affiche();
	try  {
		vect1.addition(vect6);
	}
	catch (string& s) {
		if (s=="DIMENSIONS!") {
			cerr << "erreur opération entre deux vecteurs de dimensions différentes" << endl;
		}
		if (s=="DIM<3") {
			cerr << "erreur operation impossible sans vecteur 3D" << endl;
		}
	}
	return 0;
}

