#include <iostream>
#include "../Classe_Toupie/Toupie.h"
#include "Integrateur.h"
using namespace std;

int main () {
    Objet_en_chute_libre toupie({0.0,0.0},{0.0,-9.81},2.1); //ne peut pas utiliser le vecteur g car il est en trois dimensions
    IntegrateurEulerCromer integrateur;
    integrateur.evolue(toupie, 1.0);
    cout << toupie;
    integrateur.evolue(toupie,1.0);  
    cout << toupie;  
    return 0;   
}
