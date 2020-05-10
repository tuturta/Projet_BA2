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
ostream& Toupie::affiche_parametres(ostream& out) const {
    out << "Paramètre : " << P << endl;
    out << "Dérivée : " << P_point << endl;
    out << "Masse volumique (kg m-3) : " << masse_volumique << endl;
    return out;
}


Vecteur Toupie::fonction_f() const{
        return 2*P;
}

// SURCHARGES D'OPÉRATEURS 
ostream& operator<<(std::ostream& sortie, Toupie const& toupie) {
    return toupie.affiche_parametres(sortie);
}

unique_ptr<Toupie> Toupie::clone() const{
    return unique_ptr<Toupie>(new Toupie(*this));
}
unique_ptr<Toupie> Toupie::copie() const{
    return clone();
}
void Toupie::dessine() {
    support->dessine(*this);
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
    Vecteur poids(masse()*g); //dans RO
    ref_O_to_G(poids);
    return centre_de_masse()^poids;
}

Vecteur ConeSimple::centre_de_masse() const{ // Centre de masse dans le ref d'inertie G
    return {0,0, (3.0/4.0)*hauteur};
}

Vecteur ConeSimple::fonction_f() const{ //(Cf cadre rouge page 12)
    cout << "============TESTS FONCTION F()============"<< endl;
    cout << "P_point: " << P_point <<endl;
    //1.CALCUL DE w dans RG (repère d'inertie)
        //Utilisation de la méthode
    //2.CALCUL DE W_POINT: (dans Repère d'inertie)
    Vecteur w_point(3);
    Vecteur we(w());
    we.set_coord(2,we.coeff(2) - P_point.coeff(2)); 
    cout << "we: " << we << endl;
        cout << "   matrice_inertie().inv(): " << matrice_inertie().inv() << endl;
    cout << "   matrice_inertie()*w: " << matrice_inertie()*w() << endl;
    cout << "   we^(matrice_inertie*w): " << (we^(matrice_inertie()*w())) << endl;
    w_point = matrice_inertie().inv()*(moment_poids()-(we^(matrice_inertie()*w())));
    cout << "w_point: " << w_point << endl;
    //3.CALCUL DE P_POINT_POINT: 
    Vecteur P_point_point(3);
    P_point_point.set_coord(0, w_point.coeff(0)); //Calcul de théta point point 
    
    if(P.coeff(0) == 0){ // Cas ou théta = 0
        P_point_point.set_coord(2,w_point.coeff(2)); //Modification de phi point point = w3point formule (2) p6
    }else{
        P_point_point.set_coord(1, (w_point.coeff(1)- P_point.coeff(1)*P_point.coeff(0)*cos(P.coeff(0))) / sin(P.coeff(0)) ); //Modification psi point point : formule (2) p6
        P_point_point.set_coord(2, w_point.coeff(2) + (P_point.coeff(1)*P_point.coeff(0)- w_point.coeff(1)*cos(P.coeff(0)))/sin(P.coeff(0))); //Modification phi point point formule (2) p6
    }
    
    //4.CALCUL DE G:
        //Pour le moment on le fait pas car on considère qu'il n'y a pas de glissement Va = 0
    cout << "P_point_point: " << P_point_point << endl;
    cout << "=========================================="<< endl;

    return P_point_point;
}

Vecteur ConeSimple::w() const{
    double w1(P_point.coeff(0));
    double w2(P_point.coeff(1)*sin(P.coeff(0)));
    double w3(P_point.coeff(1)*cos(P.coeff(0))+P_point.coeff(2));
    return {w1,w2,w3};
}


double ConeSimple::energie_totale() const{

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