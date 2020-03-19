#include "Matrice.h"
#include "erreurs.h"
#include <iostream>
#include <string>
using namespace std;

int main(){
    Matrice mat1({1,2,3}, {4,5,6}, {7,8,9});
    Matrice I();

    cout << I <<endl;
    cout << mat1 <<endl;
    mat1.transp();
    cout << mat1 << endl;

    return 0;
}