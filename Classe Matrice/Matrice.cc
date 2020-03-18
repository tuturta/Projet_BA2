#include <iostream>
#include "Matrice.h"
#include "erreurs.h"
using namespace std;

// DÉFINITIONS MÉTHODES

ostream& Matrice::affiche(ostream& sortie) const {
    sortie << "[ " << //continuer après avoir defini la transposee
}

// DÉFINITONS OPÉRATEURS
// INTERNES
Matrice& Matrice::operator+=(Matrice const& autre) {
    for (size_t i(0); i<colonnes.size(); ++i) {
        colonnes[i]+=autre.colonnes[i];
    }
    return *this;
}
Matrice& Matrice::operator-=(Matrice const& autre){
    for (size_t i(0); i< colonnes.size(); ++i) {
        colonnes[i]-=autre.colonnes[i];
    }
    return *this;
} 
Matrice& Matrice::operator*=(Matrice const& autre){
    /*A MEDITER
    ************
    ************
    */
}

// EXTERNES
const Matrice operator+(Matrice M1, Matrice const& M2) {
    M1+=M2;
    return M1;
}
const Matrice operator-(Matrice M1, Matrice const& M2) {
    M1-=M2;
    return M1;
}