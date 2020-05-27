#pragma once
#include <vector>
#include <initializer_list>
#include <cmath>
#include <iostream>

class Vecteur 
{
    public:

    // CONSTRUCTEURS :

    Vecteur(double x, double y, double z): coeff_({x,y,z}) { correctif_0(); } // Vecteur 3D
    Vecteur(size_t dim) : coeff_(dim,0.0) {}                                  // Vecteur nul de la dimension voulue
    Vecteur (std::initializer_list<double> const& list) {                     //Permet d'initialiser le vecteur avec des valeurs
		for (auto i : list) { coeff_.push_back(i);
		correctif_0(); } 
	}

    // OPÉRATEURS INTERNES

    Vecteur& operator+=(Vecteur const& v);       // Addition de deux vecteurs
    Vecteur& operator-=(Vecteur const& v);       // Soustraction de deux vecteurs
    Vecteur& operator^=(Vecteur const& autre);   // Produit vectoriel
    Vecteur& operator*=(double a);               // Mult par un scalaire
    double operator*(Vecteur const& v);          // Produit scalaire
    Vecteur& operator/=(double a);               // Division par un scalaire
    bool operator==(Vecteur const& autre) const; // Test d'egalite
    Vecteur operator-() const;                   // Vecteur opposé
    Vecteur operator~() const;                   // Vecteur unitaire

    // MÉTHODES :
    void augmente(double valeur);                        // Ajoute une coordonnée au vecteur (ie une dimension) qui prend la valeur "valeur"
    void set_coord(std::size_t position, double valeur); // Permet de modifier la coordonnée à la position "position" et en lui inculcant la valeur "valeur". La première coordonnées est à la position 0.
    std::ostream& affiche(std::ostream& out) const;      // Affiche le vecteur sous forme x1 x2 x3 x4 .....
    std::size_t dim() const;                             // Renvoie la dimension du vecteur
    double norme() const;                                // Renvoie la norme
    double norme2() const;                               // Renvoie la norme au carré et permet d'éviter le temps de calcul de la racine
    double coeff(size_t x) const;                        // Renvoie la coordonnée à la position x sachant que la première coordonnée est à la position x = 0
    void correctif_0();                                  // On l'utilise pour éviter d'avoir des valeurs extremement petites à la place de vrais 0 après certaines opérations.
    void modulo2pi(size_t i);                            // Modifie le coeff i en sa valeur principale modulo 2pi
    void pop_back();                                      // Diminue de 1 dimension le Vecteur --> Pour le constructeur de Toupie Chinoise

    private:

    // ATTRIBUTS :

	std::vector<double> coeff_;

};

// OPÉRATEURS EXTERNES :

const Vecteur operator+(Vecteur v, Vecteur const& w);
const Vecteur operator-(Vecteur v, Vecteur const& w);
const Vecteur operator*(Vecteur v, double a);
const Vecteur operator*(double a, Vecteur const& v);
const Vecteur operator/(Vecteur v, double a);
const Vecteur operator^(Vecteur v, Vecteur const& w);
std::ostream& operator<<(std::ostream& sortie, Vecteur const& vecteur);
