#include "Vecteur.h"
#include "erreurs.h"
#include <iostream>
#include <string>
using namespace std;

int main(){
	try{

		Vecteur vect1({2,0,1});
		Vecteur vect2(3);
		Vecteur vect3(vect1);

//SET COORDONNEES
		cout << "Vect3 = ";
		vect3.affiche(); //pour voir si le constructeur de copie par defaut convient
		vect1.set_coord(1, 1.0);
		vect3 = vect1;
//AFFICHE + test constr
		cout << "Vecteur 1 : ";
		vect1.affiche();
		cout << "Vecteur 2 : ";
		vect2.affiche();
//COMPARAISON
		vect2.set_coord(1,1.0);
		vect2.set_coord(2,1.0);
		vect2.set_coord(3,4.0);
		cout << "nouveau vect2  :";
		vect2.affiche();
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
//ADDITION v1 + v2 = ( 2 , 1, 5)
		Vecteur vect_result(3);
		vect_result = vect1.addition(vect2);
		cout << "vect1+vect2 : ";
		vect_result.affiche();
//SOUSTRACTION v1 - v2 = ( 0, -1, -3)
		vect_result = vect1.soustraction(vect2);
		cout << "vect1-vect2 : ";
		vect_result.affiche();
//MULTIPLICATION PAR UN SCALAIRE v1*2 = ( 2 , 0 , 2 )
		vect_result = vect1.mult(2);
		cout << "vect1*2 :";
		vect_result.affiche();
//PRODUIT SCALAIRE v1.v1 = 2
		double x;
		x = vect1.prod_scal(vect1);
		cout << "prod scalaire v1.v1 : " << x << endl;
	
//PRODUIT VECTORIEL v1Xv2 = (-1, -3, 1)
		vect_result = vect1.prod_vect(vect2);
		cout << "produit vectoriel v1xv2 : ";
		vect_result.affiche();
// norme2 v1 = 2
		cout << "norme au carré de v1 : " << vect1.norme2() << endl;
//norme v2 ~ 1.414
		cout << "norme de v1 : " << vect1.norme() << endl;
// Vecteur unitaire de v1 ~ ( 0.707 , 0 , 0.707)
		vect_result = vect1.unitaire();
		cout << "Vecteur unitaire de v1 : ";
		vect_result.affiche();
		cout << " de norme : " << vect_result.norme() << endl;
////TEST EXCEPTIONS
		Vecteur vect6 = {1,2}; //teste le constructeur par liste d'initialisation
		cout << "vect6 : ";
		vect6.affiche();
		vect1.addition(vect6);
		Vecteur vect7({1,2});
		vect7.prod_vect(vect6);
	}
	catch (Erreur& err) {
		if(err.code==1) {
			cerr << err.message << endl;
			////comment faire pour que ca n'arrête pas le programme 'continue'
		}
	}
	return 0;
}

