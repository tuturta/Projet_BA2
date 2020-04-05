#include <iostream>
#include <memory>
#include <fstream>
#include "../../Classe_Integrateur/Integrateur.h" 
#include "../../Classe_Integrable/Integrable.h" //Pour getP(), setP(),...
#include "../../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../../Classe_Vecteur/Vecteur.h" //Besoin pour les <<
#include "text/text_viewer.h"

using namespace std;

int main () {
    const unsigned int n(20);
    const double dt(0.01);
    double t(0);
    
 //=======================================SUPPORT TEXTUEL=================================================//      
    ofstream fichier;
    fichier.open("test.txt"); //Ouverture du fichier
    
    if(fichier.fail()) {
        //Gestion de l'erreur d'ouverture du fichier "test.txt"
    }else{
        TextViewer ecran(cout);

//-------POUR UN OBJET-------// 
    
        Objet_en_chute_libre toupie({0,1},{1.0,2.0},2.1, &ecran);
        IntegrateurEulerCromer integrateur;
        unique_ptr<IntegrateurEulerCromer> int_ptr(new IntegrateurEulerCromer(integrateur)); //Pour utiliser le evolue() de facon polymorphique lorsqu'on aura plusieurs pointeurs
    
      //Verification des donnees initiales
        cout << " vitesse initiale "<< toupie.getP_point() <<endl;
        cout << " position initiale "<< toupie.getP() << endl;
        cout << "Retour de fonction_f() : " << toupie.fonction_f() << endl;
    
     //Boucle permettant de faire n tours de evolue() et dessine()
        for(size_t i(1); i<=n ;++i){
        t+=dt;
        cout << endl << "=========TOUR " << i << "=========" << endl << endl;
        cout << "Temps : " << t << "s" <<endl;
        int_ptr->evolue(toupie, dt);
        toupie.dessine(); 
        }  
    } 
    fichier.close();
    return 0;   
}
