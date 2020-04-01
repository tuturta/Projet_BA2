#include "Integrateur.h"
#include <fstream>
//#include "../Classe_Toupie/Toupie.h"

using namespace std;

int main () {
    unsigned int n(200);
    const double dt(0.01);
    double t(0);
    Objet_en_chute_libre toupie({0,1},{1.0,2.0},2.1);
    IntegrateurEulerCromer integrateur;
    cout << " vitesse initiale "<< toupie.getP_point() <<endl;
    cout << " position initiale "<< toupie.getP() << endl;
    cout << "Retour de fonction_f() : " << toupie.fonction_f() << endl;
    
    for(size_t i(1); i<=n ;++i){
        t+=dt;
         integrateur.evolue(toupie, dt);
         cout<< endl << "=====TOUR " << n << "=====" << endl 
             << "t = " << t << endl
             << toupie <<endl; 
    }
    return 0;   
}
