#include "Vecteur.h"
#include <iostream>

using namespace std;

int main(){
	Vecteur vect1;
	Vecteur vect2;
	Vecteur vect3;

/* Cette partie
 * (1) pourrait être écrite autrement, par exemple avec des
 *     manipulateurs (set_coord) ;
 * (2) sera revue dans 2 semaines (constructeurs, surcharge des opérateurs).
 */
// v1 = (1.0, 2.0, -0.1)
	vect1.augmente(1.0); vect1.augmente(0.0); vect1.augmente(-0.1);
	vect1.set_coord(1, 2.0); // pour tester set_coord()

// v2 = (2.6, 3.5,  4.1)
	vect2.augmente(2.6); vect2.augmente(3.5); vect2.augmente(4.1);

	vect3 = vect1;

	cout << "Vecteur 1 : ";
	vect1.affiche();
	cout << endl;

	cout << "Vecteur 2 : ";
	vect2.affiche();
	cout << endl;

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
	
//v1 + v2 = ( 3.6 , 5.5, 4.0)
	
	Vecteur vect4;
	vect4 = vect1.addition(vect2);
	vect4.affiche();
//v1 - v2 = ( -1.6, -1.5, -4.2)
	vect4 = vect1.soustraction(vect2);
	vect4.affiche(); 
//v1*2 = ( 2.0 , 4.0 , -0.2 )
	vect4 = vect1.mult(2);
	vect4.affiche();
//v1.v1 = 5.01
	double x;
	x = vect1.prod_scal(vect1);
	cout << "prod scalaire : " << x << endl;
//v1Xv2 = ( 8.55 , -4.36 , -1.7 )
	Vecteur vect5;
	vect5 = vect1.prod_vect(vect2);
	cout << "produit vectoriel v1xv2 : ";
	vect5.affiche();
// norme2 v1 = 5.01
	cout << "norme au carre de v1 : " << vect1.norme2() << endl;
//norme v2 ~ 2.238
	cout << "norme de v1 : " << vect1.norme() << endl;
// Vecteur unitaire de v1 ~ ( 0.45 , 0.89 , -0.04)
	vect5 = vect1.unitaire();
	cout << "Vecteur unitaire de v1 : ";
	vect5.affiche();
	cout << " de norme : " << vect5.norme() << endl;
	
	
	return 0;
}

