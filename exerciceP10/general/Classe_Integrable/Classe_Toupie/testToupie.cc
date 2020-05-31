#include "Toupie.h"
#include "../../erreurs.h"
#include "../Integrable.h"
#include <iostream>

using namespace std;

int main() {
    try{
        TextViewer ecran(cout);

        ConeSimple cone1({0.0,0.523599,0.0}, // Angles d'Euler
                         {0.0,0.0,60.0},     // Leurs dérivées
                         0.1,                // Masse volumique
                         1.5,                // Hauteur
                         0.5,                // Rayon
                         {0.0,0.0,0.0},      // Point de contact
                         &ecran);            // support   
    

        Objet_en_chute_libre obj1({0.0,0.0,0.0},{1.0,1.0,0.0},{0.0,0.0,0.0}, &ecran);

        ConeSimple cone2({0.0,0.4,0.0}, // Angles d'Euler
                         {0.0,0.0,70.0},     // Leurs dérivées
                         0.1,                // Masse volumique
                         2.0,                // Hauteur
                         0.9,                // Rayon
                         {0.0,5.0,0.0},      // Point de contact
                         &ecran);
        
        ToupieChinoise Toupiechinoise({0.0,0.11,0.0},
                                      {50.0,0.0,0.0},
                                      0.1,
                                      0.02,
                                      0.15,
                                      {0.0,0.0,0.0},
                                      &ecran);

        ToupieChinoiseGenerale ToupiechinoiseG({0.0,0.11,0.0},
                                               {50.0,0.0,0.0},
                                               0.1,
                                               0.08,
                                               0.6,
                                               {0.0,0.0,0.0},
                                               &ecran);    
        cout << cone1 << endl;
        cout << obj1 <<endl;
        cout << cone2 << endl;
        cout << Toupiechinoise << endl;
        cout << ToupiechinoiseG << endl;
    }
    catch (Erreur& err) {
        cerr << err.message << endl;
    }
    return 0;
}

