#include "Integrateur.h"
using namespace std;


void IntegrateurEulerCromer::evolue(Toupie const& T, const double dt) const {
        T.copie()->setP_point(T.copie()->getP_point() + dt*(T.copie()->fonction_f())); //PROBLEME : l'appel est fait directement à Toupie::fonction(); sans tenir compte du masquage de ObjetEnChuteLibre::fonction();
        T.copie()->setP(T.copie()->getP() + dt*(T.copie()->getP_point()));
}




