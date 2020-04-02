#include "Integrateur.h"
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"
using namespace std;


void IntegrateurEulerCromer::evolue(Toupie const& T, const double dt) const {
        T->setP_point(T->getP_point() + dt*(T->fonction_f())); //PROBLEME : l'appel est fait directement à Toupie::fonction(); sans tenir compte du masquage de ObjetEnChuteLibre::fonction();
        T->setP(T->getP() + dt*T->getP_point());
}




