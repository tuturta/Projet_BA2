#include "Integrateur.h"
#include <fstream>
//#include "../Classe_Toupie/Toupie.h"

using namespace std;

int main () {
    ofstream out;
    out.open("test.txt");
    double dt(1);
    Objet_en_chute_libre toupie({0.0,10},{0.0,0.0},2.1);
    IntegrateurEulerCromer integrateur;
    cout << " vitesse initiale "<< toupie.getP_point() <<endl;
    cout << " position initiale "<< toupie.getP() << endl;
    cout << "Retour de fonction_f() : " << toupie.fonction_f() << endl;
    integrateur.evolue(toupie, dt);
    cout<< endl<< "=====TOUR 1=====" << endl 
        << toupie <<endl; 
    integrateur.evolue(toupie,dt);  
    cout << "=====TOUR 2=====" << endl << toupie <<endl; 
    out.close();
    return 0;   
}
