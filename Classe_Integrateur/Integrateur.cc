#include "Integrateur.h"
using namespace std;
//#include "../Classe_Toupie/Toupie.h"



void IntegrateurEulerCromer::evolue(unique_ptr<Toupie> const& T, const double dt) const {
        T->setP_point(T->getP_point() + dt*(T->fonction_f())); //PROBLEME : l'appel est fait directement à Toupie::fonction(); sans tenir compte du masquage de ObjetEnChuteLibre::fonction();
        T->setP(T->getP() + dt*T->getP_point());
}




