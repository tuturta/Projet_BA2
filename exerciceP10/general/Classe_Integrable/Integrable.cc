#include "Integrable.h"
#include "../Classe_Matrice/Matrice.h"
#include "../Classe_Vecteur/Vecteur.h"
#include <iostream>

using namespace std;

Vecteur Integrable::getP() const {
    return P;
}
Vecteur Integrable::getP_point() const {
    return P_point;
}
Vecteur Integrable::getOrigine() const{
    return origine;
}

void Integrable::setP(Vecteur const& v) {
    P=v;
}
void Integrable::setP_point(Vecteur const& v){
    P_point=v;
}

ostream& Integrable::affiche(ostream& sortie) const{
    sortie <<"paramètre : " << P << " ; dérivée : " << P_point << endl;
    return sortie;
}

Vecteur Integrable::ref_G_to_O(Vecteur const& v) const {
    return ((S().inv())*v);
}
Vecteur Integrable::ref_O_to_G(Vecteur const& v) const {
    return S()*v;
}

Matrice Integrable::S() const  {
    return Matrice ({cos(P.coeff(1)),                         sin(P.coeff(1)),                   0         },
                    {-cos(P.coeff(0))*sin(P.coeff(1)),   cos(P.coeff(1))*cos(P.coeff(0)),   sin(P.coeff(0))},
                    {sin(P.coeff(0))*sin(P.coeff(1)),    -sin(P.coeff(0))*cos(P.coeff(1)),  cos(P.coeff(0))});
}
