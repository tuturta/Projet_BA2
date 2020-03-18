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

		cout << "Censé renvoyer (4,0,2) " << (vect1+=vect3);  //vect 1 vaut maintenant 4 0 2
		cout << "Censé renvoyer (6,0,3) " << (vect1+vect3);
		cout << "Censé renvoyer 20 " << (vect1*vect1) << endl;
		cout << "Censé renvoyer (20, 0, 10) " << (vect1*=5.0); //vect1 vaut maintenant 20 0 10
		cout << "Censé renvoyer (10, 0, 5) " << (vect1/=2.0);
		cout << "Censé renvoyer (5,0,2.5) " << (vect1*0.5);
		cout << "CEnsé renvoyer (2.5, 0, 1.25) " << (0.25*vect1);
	}
	catch (Erreur& err) {
		if(err.code==1) {
			cerr << err.message << endl;
		}
	}
	return 0;
}

