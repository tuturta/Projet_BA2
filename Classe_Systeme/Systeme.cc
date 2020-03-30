#include "Systeme.h"
#include "../Classe_Toupie/Toupie.h"
#include "../Open_GL/Classe_Dessinable/general/dessinable.h"

using namespace std;

ostream& Systeme::affiche(ostream& out) const {
    for (auto const& ptr_toupie : objets) {
        if(ptr_toupie!=nullptr) {
            (*ptr_toupie).affiche_parametres(out);
        }
    }
    return out;
}

ostream& operator<<(ostream& out, Systeme const& S) {
    return S.affiche(out);
} 

void Systeme::evolue(){
    for(auto const& ptr_toupie : objets){
        if(ptr_toupie != nullptr){
            integrateur.evolue(ptr_toupie, 0.1);
        }
    }
}