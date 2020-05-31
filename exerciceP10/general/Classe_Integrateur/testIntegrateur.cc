#include <iostream>
#include <memory>
#include <fstream>
#include "Integrateur.h" 
#include "../Classe_Integrable/Integrable.h" //Pour getP(), setP(),...
#include "../Classe_Integrable/Classe_Toupie/Toupie.h" // Si jamais on veut tester avec des toupies
#include "../Classe_Vecteur/Vecteur.h" // Besoin pour les affichages de vecteurs
#include "../../text/text_viewer.h"
#include "../erreurs.h"

using namespace std;

int main () {
    const unsigned int n(80);
    const double dt(0.01);
    double t(0);
    ofstream fichier;
    fichier.open("test.txt"); //Ouverture du fichier
    
    if(fichier.fail()) {
        //Gestion de l'erreur d'ouverture du fichier "test.txt"
    }else{
        try{
            TextViewer ecran(cout); // Mettre fichier à la place de cout si on veut écire dans test.txt
            Objet_en_chute_libre toupie({0.0,1.0,0.0},{1.0,2.0,0.0}, {0.0,0.0,0.0},&ecran);
            IntegrateurEulerCromer integrateur_e;
            IntegrateurNewmark integrateur_n;
            IntegrateurRungeKutta integrateur_rk;
        //Verification des donnees initiales
            cout << " vitesse initiale "<< toupie.getP_point() <<endl;
            cout << " position initiale "<< toupie.getP() << endl;
            cout << "Retour de fonction_f() : " << toupie.fonction_f() << endl;
    
        //Boucle permettant de faire n tours de evolue() et dessine()
            for(size_t i(1); i<=n ;++i){
            t+=dt;
            cout << endl << "=========TOUR " << i << "=========" << endl << endl;
            cout << "Temps : " << t << "s" <<endl;
            integrateur_rk.evolue(toupie, dt);
            toupie.dessine(); 
            }
        }
        catch (Erreur& err) {
            cout << err.message << endl;
        }  
    } 
    fichier.close();
    return 0;   
}
