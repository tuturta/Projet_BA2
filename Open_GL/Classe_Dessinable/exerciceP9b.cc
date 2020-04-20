#include <iostream>
#include <fstream>
#include "../../Classe_Vecteur/Vecteur.h"
#include "../../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../../Classe_Systeme/Systeme.h"
#include "text/text_viewer.h"
#include "../../erreurs.h"

using namespace std;


int main() {
    const double dt(0.01); // Pas de temps
    double t(0.0); // Initialise le temps à 0
    unsigned int nombre_de_tour(30);
    try{
        //================SUPPORT TEXTUEL======================================================//
        ofstream fichier;
        fichier.open("test.txt");
        if (fichier.fail()) {
            //gérer l'erreur
        } else  {
            TextViewer ecran(cout); //mettre fichier si on veut écrire dans test.txt 
    
       //================SYSTEME=============================================================//
            IntegrateurEulerCromer integrateur;
            ConeSimple cone1({0.523599,0.0,0.0},{0.0,0.0,60.0},0.1, &ecran,1.5,0.5,{0.0,0.0,0.0});     
            ConeSimple cone2({0.785398, 0.0,0.0}, {0,0.0,40.0} ,0.1, &ecran, 1.5, 0.5, {0.1,0.0,0.0});
            Systeme systeme(integrateur, &ecran);
            systeme.ajoute_toupie(cone1);
            systeme.ajoute_toupie(cone2);

            cout << systeme << endl;
            cout << "Le système évoue et se dessine à chaque pas de temps (dt=" << dt << ") :" << endl;
            for(size_t i(1); i<=nombre_de_tour ;++i){
                t+=dt;
                cout <<endl << "----------------------------------------------------" << endl;
                cout << "Temps : " << t << "s" <<endl;
                systeme.evolue(dt);
                systeme.dessine(); 
                
            }  
        }
    }
    catch (Erreur& err) {
        if (err.code == 1) {
            cerr << err.message;
        }
    }
    return 0;
}