#include "Matrice.h"
#include "../Classe_Vecteur/Vecteur.h"
#include "../erreurs.h"
#include <iostream>
#include <string>
using namespace std;

int main(){
    try{
        Matrice mat1({1,2,3}, {4,5,6}, {7,8,9});
        Matrice I;
        Vecteur a = {1,0,0};
        cout << I;
        cout << mat1;
        cout << mat1.transp() ; //test la transpo
        cout << "Cense renvoyer 0 : " << mat1.det()<<endl;
        cout << "Cense renvoyer 1 : " << I.det()<<endl;
        cout << "Cense renvoyer matrice nulle : " << mat1.inv();
        cout << "Cense renvoyer I : "  << I.inv();
        cout << "Cense renvoyer : "  << mat1 << mat1*I;
        cout << "Cense renvoyer 1 4 7 : "  << mat1*a;
    }
    catch (Erreur& err) {
        cerr << err.message << endl;
    }
    return 0;
}