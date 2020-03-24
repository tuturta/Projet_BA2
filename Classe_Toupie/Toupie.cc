#include <iostream>
#include "Toupie.h"
#include "../Classe_Vecteur/Vecteur.h"
#include <cmath>
#include "../Classe_Matrice/Matrice.h"
using namespace std;

//=============================CLASSE TOUPIE===================================//

// METHODES
Vecteur Toupie::fonction_f() {
    return -P;
} 
ostream& Toupie::affiche(ostream& sortie) const {
    sortie << P << " # paramètres" << endl;
    sortie << P_point << " # vitesse" << endl;
    return sortie;
}
// SURCHARGES D'OPÉRATEURS 
ostream& operator<<(std::ostream& sortie, Toupie const& toupie) {
    return toupie.affiche(sortie);
}


//=============================CLASSE CONE SIMPLE===================================//

//METHODE:

double ConeSimple::masse() const{ //masse calculé grace a la formule p8
    return (1/3)*M_PI*masse_volumique*pow(rayon,2)*hauteur;
}
Matrice ConeSimple::matrice_inertie() const { // Matrice d'inertie calculé grace a la formule p8
    double I1, I3;
    I1 = masse()*((3/20)*pow(rayon,2) + (3/5)*pow(hauteur,2));
    I3 = (3/10)*masse()*pow(rayon,2);
    return Matrice(I1, I1, I3);
}
