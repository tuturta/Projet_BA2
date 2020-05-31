#include "Integrable.h"
#include "../Classe_Matrice/Matrice.h"
#include "../Classe_Vecteur/Vecteur.h"
#include "../constantes.h"
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
    for(size_t i(0); i<=2 ; ++i) { P.modulo2pi(i);   }
}
void Integrable::setP_point(Vecteur const& v){
    P_point=v;
}


void Integrable::ajoute_position_CM() {
    positions_CM.push_back(vecteurOG());
}


std::vector<Vecteur> Integrable::getPositions_CM() const {
    return positions_CM;
}

void Integrable::update_A() {
    point_de_contact_ = vecteurOA();
} 

Vecteur Integrable::getPoint_de_contact() const{
    return point_de_contact_;
}

void Integrable::setPoint_de_contact(Vecteur const& v){
    point_de_contact_=v;
}

ostream& Integrable::affiche(ostream& sortie) const{
    sortie << "Ω = ("      << P.coeff(0)       << ", " << P.coeff(1)         << ", " << P.coeff(2) 
           << ") ; Ω' = (" << P_point.coeff(0) << ", " << P_point.coeff(1)   << ", " << P_point.coeff(2) << ")" << endl;
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



//============================CLASSE OBJ CHUTE==========================================//

void Objet_en_chute_libre::dessine() {
    support->dessine(*this);
}

Vecteur Objet_en_chute_libre::fonction_f() const{
        return g;
}

Vecteur Objet_en_chute_libre::vecteurOG() const {
    return ref_G_to_O(Vecteur{0.0,0.0,0.0});
} // Objet_en_chute_libre est un point matériel pour simplifier

Vecteur Objet_en_chute_libre::vecteurOA() const {
    return ref_G_to_O(Vecteur{0.0,0.0,0.0});
} // Car c'est un point matériel

Vecteur Objet_en_chute_libre::ref_G_to_O_point(Vecteur const& point) const {
    return ref_G_to_O(point);
 } // Ici il n'y aura pas d'autre point que G, donc pas de différence avec ref_G_to_O des vecteurs

std::ostream& Objet_en_chute_libre::affiche_parametres(std::ostream& out) const {
    out << "[OBJET EN CHUTE LIBRE]" << endl;
    out << "Position : "<< P << endl << "Vitesse  : " << P_point << endl;
    return out;
}

std::ostream& Objet_en_chute_libre::affiche(std::ostream& sortie) const{
    sortie << "# x    y" << endl << " " <<  P.coeff(0) << " " << P.coeff(1) << endl;
    return sortie;
} 

ostream& operator<<(std::ostream& sortie, Objet_en_chute_libre const& objet) {
    return objet.affiche_parametres(sortie);
}