#include <iostream>
#include "Matrice.h"
#include "erreurs.h"
using namespace std;

// DÉFINITIONS MÉTHODES

ostream& Matrice::affiche(ostream& sortie) const {
   for(auto vecteur : lignes){
       cout << vecteur << endl;
   }
}

void Matrice::transp() {
    for(size_t i(0) ; i<3; ++i) {
        for(size_t j(0); j>i and j <3 ; ++j){
            lignes[i].set_coord(j, lignes[j].coeff(j));
        }
    }
}

// DÉFINITONS OPÉRATEURS
// INTERNES
Matrice& Matrice::operator+=(Matrice const& autre) {
    for (size_t i(0); i<lignes.size(); ++i) {
        lignes[i]+=autre.lignes[i];
    }
    return *this;
}
Matrice& Matrice::operator-=(Matrice const& autre){
    for (size_t i(0); i< lignes.size(); ++i) {
        lignes[i]-=autre.lignes[i];
    }
    return *this;
} 
Matrice& Matrice::operator*=(Matrice const& autre){
    // crée une matrice dont les lignes sont les colonnes de la matrice autre
    Vecteur c0(0);
    Vecteur c1(0);
    Vecteur c2(0);
    for (size_t i(0); i<3; ++i) {
        c0.augmente(autre.lignes[i].coeff(0));
        c1.augmente(autre.lignes[i].coeff(1));
        c2.augmente(autre.lignes[i].coeff(2));
    }
    Matrice mat_colonnes(c0,c1,c2);
    // Copie tampon de la matrice à modifier
    Matrice copie(*this);
    // Produit matriciel utilisant le produit scalaire des lignes de la 
    // première matrice par les colonnes de l'autre matrice:
    for (size_t l(0); l<3; ++l) {
        for (size_t c(0); c<3 ; ++c) {
            double nouveau_coeff(copie.lignes[l]*mat_colonnes.lignes[c]);
            lignes[l].set_coord(c, nouveau_coeff); //coeff de la matrice a(i,j)=ligne(i)*colonne(j)
        }
    }
   return *this;
}
Matrice& Matrice::operator*=(double a) {
    for (auto& l: lignes) {
        l*=a;
    } 
    return *this;
}
Vecteur Matrice::operator*=(Vecteur const& v) {
    return {lignes[0]*v, lignes[1]*v, lignes[2]*v};
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

std::ostream& operator<<(std::ostream& out, Matrice const& matrice){
    return matrice.affiche(out);
}
const Matrice operator*(Matrice M1, Matrice const& M2) {
    M1*=M2;
    return M1;
}
const Matrice operator*(double a, Matrice M) {
    M*=a;
    return M;
}
const Matrice operator*(Matrice M, Vecteur const& v) {
    M*=v;
    return M;
}

