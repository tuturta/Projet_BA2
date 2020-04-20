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
        TextViewer ecran(cout); // Mettre fichier si l'on veut ecrire dans un fichier, cout si l'on veut écrire dans le terminal

//-------POUR UN OBJET-------// 
    
        ConeSimple cone1({0.523599,0.0,0.0},{0.0,0.0,60.0},0.1, &ecran,1.5,0.5,{0.0,0.0,0.0});
        IntegrateurEulerCromer integrateur;
    
      //Verification des donnees initiales
        cout << " vitesse initiale "<< cone1.getP_point() <<endl;
        cout << " position initiale "<< cone1.getP() << endl;
        cout << "Retour de fonction_f() : " << cone1.fonction_f() << endl;
    
     //Boucle permettant de faire n tours de evolue() et dessine()
        for(size_t i(1); i<=n ;++i){
        t+=dt;
        cout << endl << "=========TOUR " << i << "=========" << endl << endl;
        cout << "Temps : " << t << "s" <<endl;
        integrateur.evolue(cone1, dt);
        cone1.dessine(); 
        }  
    } 
    fichier.close();
    return 0;   
}
