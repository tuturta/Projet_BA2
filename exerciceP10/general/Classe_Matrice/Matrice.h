#pragma once
#include "../Classe_Vecteur/Vecteur.h"
#include <array>
#include <iostream>

class Matrice {
private :
    std::array< Vecteur,3 > lignes;
    void correctif_0();
public :

    // CONSTRUCTEURS :

    Matrice (Vecteur const& c1 = {1,0,0}, Vecteur const& c2 = {0,1,0}, Vecteur const& c3 = {0,0,1}) : lignes({c1,c2, c3}) { correctif_0();
    } // initialise ligne par ligne et vérifie les 0, renvoie la matrice identite par defaut
    Matrice (double const& a1, double const& a2, double const& a3) : lignes({Vecteur(a1,0.0,0.0),Vecteur(0.0,a2,0.0),Vecteur(0.0,0.0,a3)}) {} //initialise une matrice diagonale

    // GETTER/SETTER si besoin :

    // MÉTHODES :

    std::ostream& affiche(std::ostream& sortie) const;
    Matrice transp() const; // renvoie la transposée de la matrice
    double det() const; 
    Matrice inv() const;
    // Opérateurs internes
    Matrice& operator+=(Matrice const& autre);
    Matrice& operator-=(Matrice const& autre);
    Matrice& operator*=(Matrice const& autre);
    Matrice& operator*=(double a);
    Vecteur operator*=(Vecteur const& v);
    
};
// OPÉRATEURS EXTERNES :
std::ostream& operator<<(std::ostream& out, Matrice const& matrice);
const Matrice operator+(Matrice M1, Matrice const& M2); // Addition de deux matrices
const Matrice operator-(Matrice M1, Matrice const& M2); // Soustraction de deux matrices
const Matrice operator*(Matrice M1, Matrice const& M2); // Produit matriciel
const Matrice operator*(double a, Matrice M);           // Produit par un scalaire
const Vecteur operator*(Matrice M, Vecteur const& v);   // Produit avec un vecteur
