#include "Integrateur.h"
//#include "../Classe_Toupie/Toupie.h"

using namespace std;

int main () {
    Objet_en_chute_libre toupie(Vecteur({0.0,0.0}),Vecteur({0.0,-9.81}),2.1);
    IntegrateurEulerCromer integrateur;
    integrateur.evolue(toupie, 1.0);
    cout << toupie;
    integrateur.evolue(toupie,1.0);  
    cout << toupie;  
    return 0;   
}
