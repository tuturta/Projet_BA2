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
    cout << "--APPEL Toupie::fonction_f()--" <<endl;

        return 2*P;
} //juste pour le test

unique_ptr<Toupie> Toupie::clone() const{
    return unique_ptr<Toupie>(new Toupie(*this));
}
unique_ptr<Toupie> Toupie::copie() const{
    return clone();
}
double Toupie::getHauteur() const{ std::cout << "toupie gethauteur" << std:: endl; return 2.0;} //pour l'instant
double Toupie::getRayon() const{ return 2.0;}   //pour l'instant

void Toupie::ajoute_position_CM() {
    Vecteur CM_refG = {0.0,0.0,0.0};
    positions_CM.push_back(ref_G_to_O_point(CM_refG));
}

std::vector<Vecteur> Toupie::getPositions_CM() const {
    return positions_CM;
}
Vecteur Toupie::ref_G_to_O_point(Vecteur const& point) const {
    //pour l'instant comme pour le cone
    double L((3.0/4.0)*getHauteur()); //A MODIFIER, UTILISER NORME DU VECTEUR AG
    double theta(P.coeff(1));
    double psi(P.coeff(0));
    Vecteur point_G( L*sin(theta)*sin(psi), L*sin(theta)*cos(psi), L*cos(theta));
    return (S().inv()*point + point_G);
}

void Toupie::dessine() {
    support->dessine(*this);
}



// POUR LE CAS GENERAL : 

double Toupie::zi(size_t i) const{
    return (2*i-1)*hauteur_/(2*N);
}

double Toupie::rayon2(size_t i) const {  //TEMPORAIRE, DOIT ETRE REDEFINI DANS CHAQUE CLASSE
    return pow((2.0*i-1.0)/(2.0*N)*rayon_,2);
}

double Toupie::masse() const{
    double masse(0.0);
    for(size_t i(1) ; i <= N; ++i){
        masse += rayon2(i);
    }
    masse *= M_PI * masse_volumique * hauteur_ / N;
    return masse;
}

double Toupie::distanceOG() const{ // où O est l'origine du solide de construction et G le centre de masse
    double somme1(0), somme2(0);
    for(size_t i(1) ; i <= N; ++i){
                somme1 += rayon2(i) * zi(i); 
                somme2 += rayon2(i);
    }
    return (somme2/somme1);
}

Matrice Toupie::matrice_inertie() const {   // Matrice d'inertie au point A dans G calculé grace a la formule de Huygens-Steiner
    Vecteur AG(vecteurAG());                // Vecteur AG dans le ref G
    Matrice delta ( { pow(AG.coeff(1),2) + pow(AG.coeff(2),2) ,       -AG.coeff(1)*AG.coeff(2)          ,        -AG.coeff(0)*AG.coeff(2)        },
                    {       -AG.coeff(1)*AG.coeff(2)          , pow(AG.coeff(0),2) + pow(AG.coeff(2),2) ,         -AG.coeff(1)*AG.coeff(2)       }, 
                    {       -AG.coeff(0)*AG.coeff(2)          ,       -AG.coeff(1)*AG.coeff(2)          , pow(AG.coeff(0),2) + pow(AG.coeff(1),2)});
    
    double ri2;                          //représente ri^ (le rayon du solide de révolution à la hauteur zo). OPTIMISATION: RI2 permet d'éviter au programme à calculer 2 fois ri ^2 pour les deux sommes
    double somme1(0),somme2(0);
    for(size_t i(1) ; i <= N; ++i){
        ri2 = rayon2(i);                    //Pour éviter de calculer 2fois le rayon au carré
        somme1 += ri2*ri2;                  //Somme des ri^4 
        somme2 += pow(zi(i),2)* ri2;
    }

    double I3 (M_PI/2.0 * masse_volumique*somme1*hauteur_/N);
    double I1 (1.0/2.0*I3 + M_PI*masse_volumique*hauteur_/N*somme2 - masse()*pow(distanceOG(),2)); //Changer I3_
    
    Matrice IG (I1, I1, I3);
    
    return (IG + masse()*delta);
}


Vecteur Toupie::vecteurAG() const{ // TEMPORAIRE POUR PAS QUE LA TOUPIE SOIT VIRTUELLE
    return {0,0, (3.0/4.0)*hauteur_};
}

Vecteur Toupie::w() const{
    
    double theta(P.coeff(1));
    double psi_P(P_point.coeff(0));
    double theta_P(P_point.coeff(1));
    double phi_P(P_point.coeff(2));
   
    Vecteur w(3);
    double w1(theta_P);
    double w2(psi_P*sin(theta));
    double w3(psi_P*cos(theta)+phi_P);
    w = {w1,w2,w3};
    
    return w;
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
    out << "Hauteur (m) : " << hauteur_ << endl;
    out << "Rayon   (m) : " << rayon_ << endl;
    out << "Origine (A) : " << origine << endl;
    return out;
}

double ConeSimple::masse() const{ //masse calculé grace a la formule p8
    return (1.0/3.0)*M_PI*masse_volumique*pow(rayon_,2)*hauteur_;
}
Matrice ConeSimple::matrice_inertie() const { // Matrice d'inertie calculé grace a la formule p8
    double I1, I3;
    I1 = masse()*((3.0/20.0)*pow(rayon_,2) + (3.0/5.0)*pow(hauteur_,2));
    I3 = (3.0/10.0)*masse()*pow(rayon_,2);
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

Vecteur ConeSimple::vecteurAG() const{ // Centre de masse dans le ref d'inertie G vu depuis le point de contact
    return {0,0, (3.0/4.0)*hauteur_};
}
Vecteur ConeSimple::ref_G_to_O_point(Vecteur const& point) const {
    double L(vecteurAG().norme());
    double theta(P.coeff(1));
    double psi(P.coeff(0));
    std::cout << "P= " << P << std::endl;
    Vecteur point_G ={L*sin(theta)*sin(psi), -L*sin(theta)*cos(psi),L*cos(theta)}; //ref absolu
    std::cout <<  "point G=" << point_G << std::endl;
    return (S().inv()*point + point_G);
}


Vecteur ConeSimple::fonction_f() const{ //(Cf cadre rouge page 12) //avec P= psi-theta-phi

    //Pour la lisibilité :
    double theta(P.coeff(1));
    double psi_P(P_point.coeff(0));
    double theta_P(P_point.coeff(1));
    double phi_P(P_point.coeff(2));

    //1.CALCUL DE w dans RG (repère d'inertie)

    //std::cout << "wRef_G = " << w << std::endl;

    //2.CALCUL DE W_POINT: (dans Repère d'inertie)
    Vecteur w_point(3);
    Vecteur we(w());
    we.set_coord(2,we.coeff(2) - phi_P); //rotation du repère (ne prend pas en compte la rotation propre de la toupie
    w_point = matrice_inertie().inv()*(moment_poids()-(we^(matrice_inertie()*w())));
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

// INVARIANTS :

double ConeSimple::energie_totale() const{
    Vecteur La(matrice_inertie()*w());
    Vecteur g_(g);
    ref_O_to_G(g_); // Le centre de masse est exprimé dans le ref G donc on doit exprimer aussi g_ dans G avant de faire le produit scalaire (sachant que la constante g est exprimé de base dans le ref galiléen O)
    return (w()*La)/2.0 - masse()*(g_*vecteurAG());
}

double ConeSimple::LAz() const{         //D'après le truc du prof, cette fonction renvoie LA3 ...
    Vecteur La(matrice_inertie()*w());
    ref_G_to_O(La);                     //Change la base du moment cinétique au point A (noté LA): Referentiel Inertie G --> Referentiel Galiléen O
    return La.coeff(2);                 // Retourne la composante z de LA exprimé dans cette nouvelle base
}

double ConeSimple::LA3() const{         //D'après le truc du prof, cette fonction renvoie LAz ...
   return (matrice_inertie()*w()).coeff(2);        //La matrice d'inertie étant exprimé dans le ref inertiel G, cela renvoie LA3 : 3eme composante du Moment cinétique au point A
}

double ConeSimple::produitMixte_awL() const{
    return (w()^(matrice_inertie()*w())).coeff(2);
}

// Getters

double ConeSimple::getHauteur() const {
    return hauteur_;
}
double ConeSimple::getRayon() const {
    return rayon_;
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
unique_ptr<Toupie> Objet_en_chute_libre::copie() const{
    return clone();
}

double Objet_en_chute_libre::getHauteur() const { return 0.0; } //le modèle de l'objet en chute libre est un point matériel
double Objet_en_chute_libre::getRayon() const { return 0.0; }


//=============================CLASSE CONE GENERAL===================================//


Vecteur ConeGeneral::fonction_f() const{
    cout << "--APPEL ConeGeneral::fonction_f()--" <<endl;
    
    //Lisibilité:
    double theta(P.coeff(1));
    double psi_P(P_point.coeff(0));
    double theta_P(P_point.coeff(1));
    double phi_P(P_point.coeff(2));
    
    //1.CALCUL DE w et MA dans RG (repère d'inertie)
        
        //Methode w()
    Vecteur MA(masse()*g.norme()*vecteurAG().norme(),0,0); // On considère que seul le poids agit sur la toupie, on néglige les autres forces  

    //2.Calcul de IA avec Huygens-Steiner

    //methode matrice_inertie()

    //3.CALCUL DE W_POINT: (dans Repère d'inertie)
    Vecteur w_point(3);
    Vecteur we(w());
    we.set_coord(2,we.coeff(2) - phi_P); //rotation du repère (ne prend pas en compte la rotation propre de la toupie
    w_point = matrice_inertie().inv()*(MA-(we^(matrice_inertie()*w())));
    //std::cout << "DW_G= " << w_point << std::endl; //1er tour bon après non
    
    //4.CALCUL DE P_POINT_POINT: 
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

    
    //5.CALCUL DE G:
        //Pour le moment on le fait pas car on considère qu'il n'y a pas de glissement Va = 0

    return P_point_point;
}

Vecteur ConeGeneral::vecteurAG() const{
    double somme1(0), somme2(0);
    double ri2;

    for(size_t i(1) ; i <= N; ++i){
        ri2 = rayon2(i);                //Optimisation pour éviter de calculer 2 fois ri^2 : une fois pour la somme 1 et une autre fois pour le ri^3 de la somme2
        somme1 += ri2;
        somme2 += ri2 * (2.0*i-1)*hauteur_/(2.0*N); //= ri3*L
    }
    return {0.0,0.0,somme2/somme1};
}

unique_ptr<ConeGeneral> ConeGeneral::clone() const{
    return unique_ptr<ConeGeneral>(new ConeGeneral(*this));
}
unique_ptr<Toupie> ConeGeneral::copie() const{
    return clone();
}

double ConeGeneral::rayon2(size_t i) const {
    return (2.0*i-1.0)/(2.0*N) *rayon_;
}

//=============================CLASSE TOUPIE CHINOISE===================================//


Vecteur ToupieChinoise::fonction_f() const{
    cout << "--APPEL ConeGeneral::fonction_f()--" <<endl;
    
    //Lisibilité:
    double theta(P.coeff(1));
    double psi_P(P_point.coeff(0));
    double theta_P(P_point.coeff(1));
    double phi_P(P_point.coeff(2));
    
    //1.CALCUL DE w et MA dans RG (repère d'inertie)
        
        //Methode w()
    Vecteur MA(masse()*g.norme()*vecteurAG().norme(),0,0); // On considère que seul le poids agit sur la toupie, on néglige les autres forces  

    //2.Calcul de IA avec Huygens-Steiner

    //methode matrice_inertie()

    //3.CALCUL DE W_POINT: (dans Repère d'inertie)
    Vecteur w_point(3);
    Vecteur we(w());
    we.set_coord(2,we.coeff(2) - phi_P); //rotation du repère (ne prend pas en compte la rotation propre de la toupie
    w_point = matrice_inertie().inv()*(MA-(we^(matrice_inertie()*w())));
    //std::cout << "DW_G= " << w_point << std::endl; //1er tour bon après non
    
    //4.CALCUL DE P_POINT_POINT: 
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

    
    //5.CALCUL DE G:
        //Pour le moment on le fait pas car on considère qu'il n'y a pas de glissement Va = 0

    return P_point_point;
}



Vecteur ToupieChinoise::vecteurAG() const{ // A revoir car different si la rotation ne se fait pas autour de l'axe de symètrie
    return {0.0,0.0,distanceOG()};
}

double ToupieChinoise::rayon2(size_t i) const {
    return 2.0*rayon_*zi(i) -  pow(zi(i),2);
}

unique_ptr<ToupieChinoise> ToupieChinoise::clone() const{
    return unique_ptr<ToupieChinoise>(new ToupieChinoise(*this));
}
unique_ptr<Toupie> ToupieChinoise::copie() const{
    return clone();
}
