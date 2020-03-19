#include "Matrice.h"
#include <iostream>
#include <string>
using namespace std;

int main(){
    Matrice mat1({1,2,3}, {4,5,6}, {7,8,9});
    Matrice I;

    cout << I <<endl;
    cout << mat1 <<endl;
    cout << mat1.transp() << endl; //test la transpo
    cout << "Cense renvoyer 0 : " << mat1.det() << endl;
    cout << "Cense renvoyer 1 : " << I.det() << endl;
    cout << "Cense renvoyer matrice nulle : " << endl << mat1.inv();
    cout << "Cense renvoyer I : " << endl << I.inv();

    return 0;
}