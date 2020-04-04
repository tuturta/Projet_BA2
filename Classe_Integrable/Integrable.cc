#include "integrable.h"
#include "../Classe_Vecteur/Vecteur.h"

Vecteur Integrable::getP() const {
    return P;
}
Vecteur Integrable::getP_point() const {
    return P_point;
}
void Integrable::setP(Vecteur const& v) {
    P=v;
}
void Integrable::setP_point(Vecteur const& v){
    P_point=v;
}