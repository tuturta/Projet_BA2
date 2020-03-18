#include "Vecteur.h"
#include <array>
#include <iostream>

class Matrice {
private :
    std::array< Vecteur,3 > colonnes;
public :
    // Constructeurs
    Matrice (Vecteur const& c1 = {1,0,0}, Vecteur const& c2 = {0,1,0}, Vecteur const& c3 = {0,0,1}) : colonnes({c1,c2, c3}) {} 
    Matrice (double const& a1, double const& a2, double const& a3) : colonnes({(a1,0,0),(0,a2,0),(0,0,a3)}) {}
    // Accesseurs/Modificateurs si besoin 
    // Méthodes
    std::ostream& affiche(std::ostream& sortie) const;
    // Opérateurs internes
    Matrice& operator+=(Matrice const& autre);
    Matrice& operator-=(Matrice const& autre);
    Matrice& operator*=(Matrice const& autre);
    Matrice& operator*=(double const& a);
    
};
// Opérateurs externes
std::ostream& operator<<(std::ostream& out, Matrice const& matrice);
const Matrice operator+(Matrice M1, Matrice const& M2);
const Matrice operator-(Matrice M1, Matrice const& M2);
const Matrice operator*(Matrice M1, Matrice const& M2);
const Matrice operator*(Matrice M, double a)

