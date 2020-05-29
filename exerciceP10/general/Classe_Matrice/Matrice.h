#pragma once
#include "../Classe_Vecteur/Vecteur.h"
#include <array>
#include <iostream>
#include "../erreurs.h"

class Matrice {

   // ATTRIBUTS : 

   private :
    std::array< Vecteur,3 > lignes; // Une matrice est un tableau formé de 3 vecteurs

   // CONSTRUCTEURS :

   public :
    Matrice (Vecteur const& c1 = {1,0,0}, Vecteur const& c2 = {0,1,0}, Vecteur const& c3 = {0,0,1}) 
    : lignes({c1,c2, c3}) { 
        if( (c1.dim()!=3) or (c2.dim()!=3) or (c3.dim()!=3) ) {
            Erreur err = {"Les matrices ne peuvent pas être de dimension autre que 3x3"};
            throw err;
        }
        correctif_0();
     } // Initialise ligne par ligne et vérifie les 0, renvoie la matrice identité par defaut
    
    Matrice (double const& a1, double const& a2, double const& a3) 
    : lignes({Vecteur(a1,0.0,0.0),Vecteur(0.0,a2,0.0),Vecteur(0.0,0.0,a3)}) {} // Matrice diagonale


   // MÉTHODES :
   private : 
    void correctif_0();
   public :
    std::ostream& affiche(std::ostream& sortie) const; // Affichage d'une matrice
    Matrice transp() const;                            // Transposée de la matrice
    double det() const;                                // Déterminant de la matrice
    Matrice inv() const;                               // Inverse de la matrice 
   
   // OPÉRATEURS INTERNES :

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
