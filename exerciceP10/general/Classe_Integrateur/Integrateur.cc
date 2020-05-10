#include "Integrateur.h"
#include "../Classe_Integrable/Integrable.h"
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../Classe_Vecteur/Vecteur.h" // Pour les produits entre vecteurs
#include "../Classe_Systeme/Systeme.h"
#include <iostream>

//ESSAI ARTHUR *****************************************
//#include "../dessinable.h"

using namespace std;


void IntegrateurEulerCromer::evolue(Toupie& T, const double dt) const {
        T.setP_point(T.getP_point() + dt*((T.copie())->fonction_f())); 
        T.setP(T.getP() + dt*((T.copie())->getP_point()));
}

void IntegrateurEulerCromer::evolue(Systeme& S, const double dt) const {
    for(size_t i(0) ; i < S.size() ; ++i){
            unique_ptr<Toupie> temp(S.getToupie(i));
            evolue(*temp,dt);
            S.setToupie(i, *temp);
        }
}





