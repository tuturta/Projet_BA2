#include "Integrateur.h"
using namespace std;
//#include "../Classe_Toupie/Toupie.h"



void IntegrateurEulerCromer::evolue(Toupie& T, double dt) const {
        T.setP_point(T.getP_point() + dt*(T.fonction_f()));
        T.setP(T.getP() + dt*T.getP_point());
    }
void IntegrateurEulerCromer::evolue_chute(Objet_en_chute_libre& O,  double dt) const {
    O.setP_point(O.getP_point() + dt*(O.fonction_f()));
    O.setP(O.getP() + dt*O.getP_point());
}

void IntegrateurEulerCromer::evolue_nfois(Toupie& T, double dt, unsigned int n) const{
    for(size_t i(1); i<=n ; ++i){
        evolue(T,dt);
        cout << T << endl;
        }
}
void IntegrateurEulerCromer::evolue_chute_nfois(Objet_en_chute_libre& O, double dt, unsigned int n) const {
    for(size_t i(1); i<=n ; ++i){
        cout << "t= " << 0.01*i << endl;
        evolue_chute(O,dt);
        cout << O << endl;
        }
}
