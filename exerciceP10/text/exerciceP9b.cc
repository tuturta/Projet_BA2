#include <iostream>
#include <fstream>
#include "../general/Classe_Vecteur/Vecteur.h"
#include "../general/Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../general/Classe_Systeme/Systeme.h"
#include "../general/Classe_Integrateur/Integrateur.h"

#include "text_viewer.h"
#include "../general/erreurs.h"

using namespace std;


int main() {
    const double dt(0.01); // Pas de temps
    double t(0.0); // Initialise le temps à 0
    unsigned int nombre_de_tour(10);
    try{
        //================SUPPORT TEXTUEL======================================================//
        ofstream fichier;
        fichier.open("valeursConeGeneral.txt");
        if (fichier.fail()) {
            //gérer l'erreur
        } else  {
            TextViewer ecran(cout); //mettre fichier si on veut écrire dans test.txt
    
       //================SYSTEME=============================================================//
            IntegrateurEulerCromer integrateur_e;
            IntegrateurNewmark  integrateur_n;
            IntegrateurRungeKutta integrateur_rk;

            ConeSimple cone1({0.0,0.523599,0.0},{0.0,0.0,60.0},0.1,1.5,0.5,{0.0,0.0,0.0}, &ecran);
            ConeGeneral cone2({0.0,0.523599,0.0},{0.0,0.0,60.0},0.1,1.5,0.5,{0.0,0.0,0.0}, &ecran);
            ToupieChinoise Toupiechinoise({0.0,0.11,0.0},{50.0,0.0,0.0},0.1,0.02,0.15,{0.0,0.0,0.0}, &ecran);
            ToupieRoulante ToupieChinoiseG({0.0,0.11,0.0},{50.0,0.0,0.0},0.1,0.02,0.15,{0.0,0.0,0.0}, &ecran);

            Systeme systeme(&ecran);
            //systeme.ajoute_toupie(cone1);
            //systeme.ajoute_toupie(cone2);
            systeme.ajoute_toupie(Toupiechinoise);
            //systeme.ajoute_toupie(ToupieChinoiseG);

            cout << systeme << endl;
            cout << "Le système évolue et se dessine à chaque pas de temps (dt=" << dt << ") :" << endl;
            for(size_t i(1); i<=nombre_de_tour ;++i){
                t+=dt;
                cout <<endl << "----------------------------------------------------" << endl;
                cout << "Temps : " << t << "s" <<endl;
                integrateur_e.evolue(systeme,dt);
                systeme.dessine(); 

            }  
        }
    }
    catch (Erreur& err) {
            cerr << err.message;
    }
    return 0;
}
