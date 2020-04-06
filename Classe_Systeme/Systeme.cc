#include <iostream>
#include "Systeme.h"
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../Classe_Integrateur/Integrateur.h"
#include "../Open_GL/Classe_Dessinable/general/support_a_dessin.h"


using namespace std;

ostream& Systeme::affiche_parametres(ostream& out) const {
    for (auto const& ptr_toupie : objets) {
        if(ptr_toupie!=nullptr) {
            ptr_toupie->affiche_parametres(out);
        }
    }
    return out;
}

ostream& operator<<(ostream& out, Systeme const& S) {
    return S.affiche_parametres(out);
} 

void Systeme::evolue(const double dt){
    for(auto const& ptr_toupie : objets){
        if(ptr_toupie != nullptr){
            integrateur.evolue(*ptr_toupie, dt);
        }
    }
}

ostream& Systeme::affiche(ostream& out) const {
    for(auto const& ptr_toupie : objets){
        if(ptr_toupie != nullptr){
            ptr_toupie->affiche(out);
        }
    }
    return out;
}
    
void Systeme::ajoute_toupie(Toupie const& nouvelle){
    objets.push_back(nouvelle.copie());
}

void Systeme::dessine() {
    support->dessine(*this);
} 