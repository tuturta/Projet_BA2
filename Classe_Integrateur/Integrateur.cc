#include "Integrateur.h"
using namespace std;
//#include "../Classe_Toupie/Toupie.h"



void IntegrateurEulerCromer::evolue(Toupie& T, const double dt) const {
        T.setP_point(T.getP_point() + dt*(T.fonction_f())); //PROBLEME : l'appel est fait directement à Toupie::fonction(); sans tenir compte du masquage de ObjetEnChuteLibre::fonction();
        T.setP(T.getP() + dt*T.getP_point());
    }

void IntegrateurEulerCromer::evolue_nfois(Toupie& T, double dt, unsigned int n) const{
    for(size_t i(1); i<=n ; ++i){
        evolue(T,dt);
        cout << T << endl;
        }
}
