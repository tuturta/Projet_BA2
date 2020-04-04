#define _USE_MATH_DEFINES //Pour régler le problème de M_PI non reconnu par le compilateur sur windows
#include <cmath>    
#include "Toupie.h"
#include <iostream>
using namespace std;

//=============================CLASSE TOUPIE===================================//

// METHODES
ostream& Toupie::affiche(ostream& sortie) const {
    sortie << P << " # parametres" << endl;
    sortie << P_point << " # vitesse" << endl;
    return sortie;
}

ostream& Toupie::affiche_parametres(ostream& out) const {
    out << "Paramètre : " << P << endl;
    out << "Dérivée : " << P_point << endl;
    out << "Masse volumique (kg m-3) :" << masse_volumique << endl;
    return out;
}



// SURCHARGES D'OPÉRATEURS 
ostream& operator<<(std::ostream& sortie, Toupie const& toupie) {
    return toupie.affiche(sortie);
}


//=============================CLASSE CONE SIMPLE===================================//

//METHODES:

ostream& ConeSimple::affiche_parametres(ostream& out) const {
    Toupie::affiche_parametres(out);
    out << "Hauteur (m) : " << hauteur << endl;
    out << "Rayon (m) : " << rayon << endl;
    out << "Origine (A) : " << origine << endl;
}

double ConeSimple::masse() const{ //masse calculé grace a la formule p8
    return (1/3)*M_PI*masse_volumique*pow(rayon,2)*hauteur;
}
Matrice ConeSimple::matrice_inertie() const { // Matrice d'inertie calculé grace a la formule p8
    double I1, I3;
    I1 = masse()*((3/20)*pow(rayon,2) + (3/5)*pow(hauteur,2));
    I3 = (3/10)*masse()*pow(rayon,2);
    return Matrice(I1, I1, I3);
}

unique_ptr<ConeSimple> ConeSimple::clone() const{
    return unique_ptr<ConeSimple>(new ConeSimple(*this));
}
unique_ptr<Integrable> ConeSimple::copie() const{
    return clone();
}

// Méthode virtuelle dessinable

void ConeSimple::dessine() {
    support->dessine(*this);
} 

//============================CLASSE OBJ CHUTE=====================================//

void Objet_en_chute_libre::dessine() {
    support->dessine(*this);
}

Vecteur Objet_en_chute_libre::fonction_f() const{
        return {0,-9.81};
}