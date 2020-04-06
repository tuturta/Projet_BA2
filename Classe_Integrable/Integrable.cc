#include "integrable.h"
#include "../Classe_Vecteur/Vecteur.h"
#include <iostream>

using namespace std;

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

ostream& Integrable::affiche(ostream& sortie) const {
    sortie <<"paramètre : " << P << " ; dérivée : " << P_point << endl;
    return sortie;
}