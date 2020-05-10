#include "Integrateur.h"
#include "../Classe_Integrable/Integrable.h"
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../Classe_Vecteur/Vecteur.h" // Pour les produits entre vecteurs
#include "../Classe_Systeme/Systeme.h"
#include <iostream>

using namespace std;


void IntegrateurEulerCromer::evolue(Toupie& T, const double dt) const {
        T.setP_point(T.getP_point() + dt*((T.copie())->fonction_f())); //PROBLEME : l'appel est fait directement à Toupie::fonction(); sans tenir compte du masquage de ObjetEnChuteLibre::fonction();
        /*std::cout << "Dpsi = " << T.getP_point().coeff(0) << std::endl;
        std::cout << "Dtheta = " << T.getP_point().coeff(1) << std::endl;
        std::cout << "Dphi = " << T.getP_point().coeff(2) << std::endl;*/

        T.setP(T.getP() + dt*((T.copie())->getP_point()));

        /*std::cout << "psi = " << T.getP().coeff(0) << std::endl;
        std::cout << "theta = " << T.getP().coeff(1) << std::endl;
        std::cout << "phi = " << T.getP().coeff(2) << std::endl;*/

        T.ajoute_position_CM(); // ajoute cette nouvelle position du CM ds le vector nécessaire pour la trace
}

void IntegrateurEulerCromer::evolue(Systeme& S, const double dt) const {
    for(size_t i(0) ; i < S.size() ; ++i){
            unique_ptr<Toupie> temp(S.getToupie(i));
            evolue(*temp,dt);
            S.setToupie(i, *temp);
        }
}





