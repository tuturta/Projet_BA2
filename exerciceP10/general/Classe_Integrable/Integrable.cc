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
Vecteur Integrable::getPoint_de_conact() const{
    return point_de_contact;
}

void Integrable::setP(Vecteur const& v) {
    P=v;
    for(size_t i; i<=3 ; ++i) { P.modulo2pi(i);   }
}
void Integrable::setP_point(Vecteur const& v){
    P_point=v;
}

void Integrable::setPoint_de_contact(Vecteur const& v){
    point_de_contact=v;
}

ostream& Integrable::affiche(ostream& sortie) const{
    sortie << "Ω = " << P.coeff(0) << " " << P.coeff(1) << " " << P.coeff(2) << " ; Ω' = " << P_point.coeff(0) << " " << P_point.coeff(1) << " " << P_point.coeff(2) << endl;
    sortie << "A = " << point_de_contact << endl;
    return sortie;
}

Vecteur Integrable::ref_G_to_O(Vecteur const& v) const {
    return ((S().inv())*v);
}
Vecteur Integrable::ref_O_to_G(Vecteur const& v) const {
    return S()*v;
}

Matrice Integrable::S() const  {

    double psi(P.coeff(0));
    double theta(P.coeff(1));

    return Matrice ( {cos(psi)            ,   sin(psi)            ,  0          },
                     {-cos(theta)*sin(psi),   cos(psi)*cos(theta) ,  sin(theta) },
                     {sin(theta)*sin(psi) ,   -sin(theta)*cos(psi),  cos(theta) }   );
}
