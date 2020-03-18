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

//TESTS OPERATEURS:
		cout << "Cense renvoyer 0 : " << (vect1 == vect2) << endl; //test inegalite --> renvoie 0 
		cout << "Cense renvoyer 1 : " << (vect1 == vect1) << endl;// test egalite ---> 1
		cout << "Cense renvoyer ( 0 0 0 ) : " << (vect1 -= vect1) << endl;// test 
		cout << "Cense renvoyer ( 1 1 1 ) : " << vect3 - Vecteur({1,-1,0}) << endl;
		cout << "Cense renvoyer ( -2 0 -1 ) : " << -vect3 << endl;
	}
	catch (Erreur& err) {
		if(err.code==1) {
			cerr << err.message << endl;
		}
	}
	return 0;
}
