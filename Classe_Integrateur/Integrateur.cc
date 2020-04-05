#include "Integrateur.h"
#include "../Classe_Integrable/Integrable.h"
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../Classe_Vecteur/Vecteur.h" // Pour les produits entre vecteurs

using namespace std;


void IntegrateurEulerCromer::evolue(Toupie& T, const double dt) const {
        T.setP_point(T.getP_point() + dt*((T.copie())->fonction_f())); //PROBLEME : l'appel est fait directement à Toupie::fonction(); sans tenir compte du masquage de ObjetEnChuteLibre::fonction();
        T.setP(T.getP() + dt*((T.copie())->getP_point()));
}




