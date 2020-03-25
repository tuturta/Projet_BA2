#include "Integrateur.h"
//#include "../Classe_Toupie/Toupie.h"



void IntegrateurEulerCromer::evolue(Toupie& T, double dt) const {
        T.setP_point(T.getP_point() + dt*(T.fonction_f()));
        T.setP(T.getP() + dt*T.getP());
    }

void IntegrateurEulerCromer::evolue_nfois(Toupie& T, double dt, unsigned int n) const{
    for(size_t i(1); i<=n ; ++i){
        evolue(T,dt);
        }
}
