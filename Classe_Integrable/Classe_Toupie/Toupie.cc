#define _USE_MATH_DEFINES //Pour régler le problème de M_PI non reconnu par le compilateur sur windows
#include <cmath>    
#include <iostream>
#include "../../constantes.h"
#include "Toupie.h"
#include "../Integrable.h"
#include "../../Classe_Vecteur/Vecteur.h"
#include "../../Classe_Matrice/Matrice.h"
#include "../../Open_GL/Classe_Dessinable/general/support_a_dessin.h"
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

Matrice Toupie::S() const  {
    return Matrice({cos(P.coeff[1]),                    sin(P.coeff[1]),                   0},
                   {-cos(P.coeff[0])*sin(P.coeff[1]),   cos(P.coeff[1])*cos(P.coeff[0]),   sin(P.coeff[0])},
                   {sin(P.coeff[0])*cos(P.coeff[1]),    -sin(P.coeff[0])*cos(P.coeff[1]),  cos(P.coeff[0])});
}

void Toupie::ref_G_to_O(Vecteur& v) {
    v=((S().inv())*v);
}
void Toupie::ref_O_to_G(Vecteur& v) {
    v=S()*v;
}

Vecteur Toupie::fonction_f() const{
        return 2*P;
}

// SURCHARGES D'OPÉRATEURS 
ostream& operator<<(std::ostream& sortie, Toupie const& toupie) {
    return toupie.affiche(sortie);
}

unique_ptr<Toupie> Toupie::clone() const{
    return unique_ptr<Toupie>(new Toupie(*this));
}
unique_ptr<Integrable> Toupie::copie() const{
    return clone();
}
void Toupie::dessine() {
    support->dessine(*this);
} 

//=============================CLASSE CONE SIMPLE===================================//

//METHODES:

ostream& ConeSimple::affiche_parametres(ostream& out) const {
    out << "CONE SIMPLE " << endl;
    Toupie::affiche_parametres(out);
    out << "Hauteur (m) : " << hauteur << endl;
    out << "Rayon (m) : " << rayon << endl;
    out << "Origine (A) : " << origine << endl;
    return out;
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

Vecteur ConeSimple::moment_poids() const {
    Vecteur AG = {3/4*hauteur, 0, 0}; // tout est dnas le ref RG
    Vecteur poids(masse()*g); //dans RO
    ref_O_to_G(poids);
    return AG*poids;
}

Vecteur ConeSimple::fonction_f() const{
    
    //1.CALCUL DE w dans RG (repère d'inertie)
    Vecteur w(3);
    double w1(P_point.coeff[0]);
    double w2(P_point.coeff[1]*sin(P.coeff[0]));
    double w3(P_point.coeff[1]*cos(P.coeff[0])+P_point.coeff[2]);
    w = {w1,w2,w3};
    Vecteur moment_forces_A(moment_poids()); //Vecteur moment de force au point de contact
    Matrice IA(matrice_inertie()); //Matrice d'inertie d'un cone simple dans RG
    //reprendre IA point ...

    //2.CALCUL DE W_POINT: (dans Repère d'inertie)
    Vecteur w_point(3);
    Vecteur we(w);
    we.set_coord(2,we.coeff(2) - P_point.coeff(2)); 
    w_point = matrice_inertie().inv()*(moment_poids()-(we^(matrice_inertie()*w)));
    //3.CALCUL DE P_POINT_POINT:

    //4.CALCUL DE G:
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

unique_ptr<Objet_en_chute_libre> Objet_en_chute_libre::clone() const{
    return unique_ptr<Objet_en_chute_libre>(new Objet_en_chute_libre(*this));
}
unique_ptr<Integrable> Objet_en_chute_libre::copie() const{
    return clone();
}