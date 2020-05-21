#define _USE_MATH_DEFINES //Pour régler le problème de M_PI non reconnu par le compilateur sur windows
#include <cmath>    
#include <iostream>
#include "../../constantes.h"
#include "Toupie.h"
#include "../Integrable.h"
#include "../../Classe_Vecteur/Vecteur.h"
#include "../../Classe_Matrice/Matrice.h"
#include "../../support_a_dessin.h"
using namespace std;

//=============================CLASSE TOUPIE===================================// 

// METHODES

ostream& Toupie::affiche_parametres(ostream& out) const {
    out << "Paramètre : " << P << endl;
    out << "Dérivée : " << P_point << endl;
    out << "Masse volumique (kg m-3) : " << masse_volumique << endl;
    return out;
}


Vecteur Toupie::fonction_f() const{
        return 2*P;
} //juste pour le test

unique_ptr<Toupie> Toupie::clone() const{
    return unique_ptr<Toupie>(new Toupie(*this));
}
unique_ptr<Toupie> Toupie::copie() const{
    return clone();
}
double Toupie::getHauteur() const{ std::cout << "toupie gethauteur" << std:: endl; return 1.0;} //pour l'instant
double Toupie::getRayon() const{ return 1.0;}   //pour l'instant

void Toupie::ajoute_position_CM() {
    Vecteur CM_refG = {0.0,0.0,0.0};
    positions_CM.push_back(ref_G_to_O_point(CM_refG));
}

std::vector<Vecteur> Toupie::getPositions_CM() const {
    return positions_CM;
}
Vecteur Toupie::ref_G_to_O_point(Vecteur const& point) const {
    //pour l'instant comme pour le cone
    double L((3.0/4.0)*getHauteur());
    double theta(P.coeff(1));
    double psi(P.coeff(0));
    Vecteur point_G( L*sin(theta)*sin(psi), L*sin(theta)*cos(psi), L*cos(theta));
    return (S().inv()*point + point_G);
}
void Toupie::dessine() {
    support->dessine(*this);
}


// SURCHARGES D'OPÉRATEURS 

ostream& operator<<(std::ostream& sortie, Toupie const& toupie) {
    return toupie.affiche_parametres(sortie);
}


//=============================CLASSE CONE SIMPLE===================================//

//METHODES:

ostream& ConeSimple::affiche_parametres(ostream& out) const {
    out << "CONIQUE SIMPLE " << endl;
    Toupie::affiche_parametres(out);
    out << "Hauteur (m) : " << hauteur << endl;
    out << "Rayon   (m) : " << rayon << endl;
    out << "Origine (A) : " << origine << endl;
    return out;
}

double ConeSimple::masse() const{ //masse calculé grace a la formule p8
    return (1.0/3.0)*M_PI*masse_volumique*pow(rayon,2)*hauteur;
}
Matrice ConeSimple::matrice_inertie() const { // Matrice d'inertie calculé grace a la formule p8
    double I1, I3;
    I1 = masse()*((3.0/20.0)*pow(rayon,2) + (3.0/5.0)*pow(hauteur,2));
    I3 = (3.0/10.0)*masse()*pow(rayon,2);
    return Matrice(I1, I1, I3);
}

unique_ptr<ConeSimple> ConeSimple::clone() const{
    return unique_ptr<ConeSimple>(new ConeSimple(*this));
}
unique_ptr<Toupie> ConeSimple::copie() const{
    return clone();
}


Vecteur ConeSimple::moment_poids() const{
    Vecteur poids(masse()*g); //dans le ref absolu
    poids=ref_O_to_G(poids);
    return vecteurAG()^poids;
}

Vecteur ConeSimple::vecteurAG() const{    // Centre de masse dans le ref d'inertie G vu depuis le point de contact
    return {0,0, (3.0/4.0)*hauteur};
}
Vecteur ConeSimple::ref_G_to_O_point(Vecteur const& point) const {
    double L((3.0/4.0)*hauteur);
    double theta(P.coeff(1));
    double psi(P.coeff(0));
    Vecteur point_G ={L*sin(theta)*sin(psi), -L*sin(theta)*cos(psi),L*cos(theta)}; //ref absolu
    return (S().inv()*point + point_G);
}


Vecteur ConeSimple::fonction_f() const{   //(Cf cadre rouge page 12) //avec P= psi-theta-phi

    //Pour la lisibilité :
    double psi(P.coeff(0));
    double theta(P.coeff(1));
    double phi(P.coeff(2));
    double psi_P(P_point.coeff(0));
    double theta_P(P_point.coeff(1));
    double phi_P(P_point.coeff(2));


    //1.CALCUL DE w dans RG (repère d'inertie)
    Vecteur w(3);
    double w1(theta_P);
    double w2(psi_P*sin(theta));
    double w3(psi_P*cos(theta)+phi_P);
    w = {w1,w2,w3};
    //std::cout << "wRef_G = " << w << std::endl;

    //2.CALCUL DE W_POINT: (dans Repère d'inertie)
    Vecteur w_point(3);
    Vecteur we(w);
    we.set_coord(2,we.coeff(2) - phi_P); //rotation du repère (ne prend pas en compte la rotation propre de la toupie
    w_point = matrice_inertie().inv()*(moment_poids()-(we^(matrice_inertie()*w)));
    //std::cout << "DW_G= " << w_point << std::endl; //1er tour bon après non

    //3.CALCUL DE P_POINT_POINT: 
    Vecteur P_point_point(3);
    P_point_point.set_coord(1, w_point.coeff(0)); //Calcul de théta point point
    
    if(abs(theta) < eps){ //test theta=0.0
        P_point_point.set_coord(2,w_point.coeff(2)); //Modification de phi point point = w3point formule (2) p6
    }else{
        P_point_point.set_coord(0, (w_point.coeff(1) - psi_P*theta_P*cos(theta)) / sin(theta) ); //Modification psi point point : formule (2) p6
        P_point_point.set_coord(2, w_point.coeff(2) - P_point_point.coeff(0)*cos(theta) + psi_P*theta_P*sin(theta)); //Modification phi point point formule (2) p6
    }

    /*std::cout << "DDpsi =" << P_point_point.coeff(0) << std::endl;
    std::cout << "DDtheta =" << P_point_point.coeff(1) << std::endl;
    std::cout << "DDphi =" << P_point_point.coeff(2) << std::endl;*/

    //4.CALCUL DE G:
    //Pour le moment on le fait pas car on considère qu'il n'y a pas de glissement Va = 0

    return P_point_point;
}

// Getters

double ConeSimple::getHauteur() const {
    return hauteur;
}
double ConeSimple::getRayon() const {
    return rayon;
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
        return {0,-9.81,0.0};
}

unique_ptr<Objet_en_chute_libre> Objet_en_chute_libre::clone() const{
    return unique_ptr<Objet_en_chute_libre>(new Objet_en_chute_libre(*this));
}
unique_ptr<Toupie> Objet_en_chute_libre::copie() const{
    return clone();
}

double Objet_en_chute_libre::getHauteur() const { return 0.0; } //le modèle de l'objet en chute libre est un point matériel
double Objet_en_chute_libre::getRayon() const { return 0.0; }

