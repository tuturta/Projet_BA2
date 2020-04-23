#include "Integrateur.h"
#include "../Classe_Integrable/Integrable.h"
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../Classe_Vecteur/Vecteur.h" // Pour les produits entre vecteurs
#include "../Classe_Systeme/Systeme.h"
#include "../dessinable.h"

using namespace std;


void IntegrateurEulerCromer::evolue(Toupie& T, const double dt) const {
    cout << "appel evolue(toupie)" <<endl;
        T.setP_point(T.getP_point() + dt*((T.copie())->fonction_f())); //PROBLEME : l'appel est fait directement à Toupie::fonction(); sans tenir compte du masquage de ObjetEnChuteLibre::fonction();
        T.setP(T.getP() + dt*((T.copie())->getP_point()));
}

void IntegrateurEulerCromer::evolue(Systeme& S, const double dt) const {
    cout << "appel evolue(systeme) " <<endl;
    for(size_t i(0) ; i < S.size() ; ++i){
            Toupie temp(S.getToupie(i));
            evolue(temp,dt);
            S.setToupie(i, temp);
        }
}

void IntegrateurEulerCromer::evolue(Dessinable& contenu, const double dt) const {
    cout << "appel evolue(Dessinable) " << endl;
}




