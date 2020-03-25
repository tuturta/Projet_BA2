#include "Integrateur.h"
#include <fstream>
//#include "../Classe_Toupie/Toupie.h"

using namespace std;

int main () {
    ofstream out;
    out.open("test.txt");
    unsigned int n(30);
    double dt(0.1);
    Objet_en_chute_libre toupie({0,10},{4.0,0.0},2.1);
    IntegrateurEulerCromer integrateur;
    cout << " vitesse initiale "<< toupie.getP_point() <<endl;
    cout << " position initiale "<< toupie.getP() << endl;
    cout << "Retour de fonction_f() : " << toupie.fonction_f() << endl;
    
    for(size_t i(1); i<=n ;++i){
         integrateur.evolue(toupie, dt);
         cout<< endl<< "=====TOUR " << n << "=====" << endl 
             << toupie <<endl; 
     integrateur.evolue(toupie,dt);  
    }
    out.close();
    return 0;   
}
