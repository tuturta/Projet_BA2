#include <iostream>
#include <fstream>
#include <iomanip>
#include "../general/Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../general/Classe_Integrateur/Integrateur.h"
#include "text_viewer.h"
#include "../../erreurs.h"

using namespace std;


int main() {
    const double dt(0.01); // Pas de temps
    double t(0.0); // Initialise le temps à 0
    unsigned int nombre_de_tour(50);
    try{
        //================SUPPORT TEXTUEL======================================================//
        ofstream fichier;
        fichier.open("testInvariantsTC.txt");
        if (fichier.fail()) {
            //gérer l'erreur
        } else  {
            TextViewer ecran(fichier); //mettre fichier si on veut écrire dans test.txt 
    
       //================SYSTEME=============================================================//
            IntegrateurEulerCromer integrateur;
            ConeSimple cone1({0.0,0.523599,0.0},{0.0,0.0,60.0},0.1,1.5,0.5,{0.0,0.0,0.0}, &ecran);
            fichier << "#Temps:  Energie totale:             LAz:             LAa:         a.(w^L):" <<endl;   
            for(size_t i(1); i<=nombre_de_tour ;++i){
                cout << cone1 << endl;
                fichier << setw(7) << t 
                        << setw(17) << cone1.energie_totale() 
                        << setw(17) << cone1.LAz() 
                        << setw(17) << cone1.LA3()
                        << setw(17) << cone1.produitMixte_awL() << endl;
                
                
                cout << t << " " << cone1.energie_totale() <<endl;
                integrateur.evolue(cone1,dt);
                t+=dt;

            }  
        }
        fichier.close();
    }
    catch (Erreur& err) {
        if (err.code == 1) {
            cerr << err.message;
        }
    }
    return 0;
}
