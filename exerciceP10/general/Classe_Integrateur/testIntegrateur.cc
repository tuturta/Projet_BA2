#include <iostream>
#include <memory>
#include <fstream>
#include "Integrateur.h" 
#include "../Classe_Integrable/Integrable.h" //Pour getP(), setP(),...
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../Classe_Vecteur/Vecteur.h" //Besoin pour les <<
#include "../Open_GL/Classe_Dessinable/text/text_viewer.h"

using namespace std;

int main () {
    const unsigned int n(20);
    const double dt(0.01);
    double t(0);
    ofstream fichier;
    fichier.open("test.txt"); //Ouverture du fichier
    
    if(fichier.fail()) {
        //Gestion de l'erreur d'ouverture du fichier "test.txt"
    }else{
        TextViewer ecran(cout);
        Objet_en_chute_libre toupie({0,1},{1.0,2.0},2.1, &ecran);
        IntegrateurEulerCromer integrateur;
    
      //Verification des donnees initiales
        cout << " vitesse initiale "<< toupie.getP_point() <<endl;
        cout << " position initiale "<< toupie.getP() << endl;
        cout << "Retour de fonction_f() : " << toupie.fonction_f() << endl;
    
     //Boucle permettant de faire n tours de evolue() et dessine()
        for(size_t i(1); i<=n ;++i){
        t+=dt;
        cout << endl << "=========TOUR " << i << "=========" << endl << endl;
        cout << "Temps : " << t << "s" <<endl;
        integrateur.evolue(toupie, dt);
        toupie.dessine(); 
        }  
    } 
    fichier.close();
    return 0;   
}
