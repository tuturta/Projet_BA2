#include <iostream>
#include "C:\Users\arthu\Desktop\Programmation\Projet_BA2\Classe_Vecteur\Vecteur.h"
#include "Matrice.h"
using namespace std;

// DÉFINITIONS MÉTHODES

ostream& Matrice::affiche(ostream& sortie) const {
   for(auto vecteur : lignes){
       sortie << vecteur << endl;
   }
   return sortie;
}

Matrice Matrice::transp() const{
    Matrice retour(*this);
    for(size_t i(0) ; i<3; ++i) {
        for(size_t j(0); j <3 ; ++j){
            if(j>i){
                retour.lignes[i].set_coord(j+1, lignes[j].coeff(i));
                retour.lignes[j].set_coord(i+1, lignes[i].coeff(j));
            }
        }
    }
    return retour;
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
/*Matrice& Matrice::operator*=(Matrice const& autre){
    Vecteur c1(0);
    Vecteur c2(0);
    Vecteur c3(0);
    for (size_t i(0); i<3; ++i) {
        c1.autre.lignes[i].coeff(0);
        c2[i]=autre.lignes
    }
}*/

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
