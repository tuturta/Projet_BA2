#pragma once
#include <vector>
#include <initializer_list>
#include <cmath>
#include <iostream>

class Vecteur 
{
public:
// Constructeurs
	Vecteur(double x, double y, double z): coeff_({x,y,z}) { correctif_0(); } //vecteur 3D
	Vecteur(size_t dim) : coeff_(dim,0.0) {}//Vecteur nul de la dimension voulue
	Vecteur (std::initializer_list<double> const& list) {  //Permet d'initialiser la matrice avec des valeurs
		for (auto i : list) { coeff_.push_back(i);
		correctif_0(); } 
	}
// Opérateurs internes (prototypes)
	Vecteur& operator+=(Vecteur const& v); // addition de deux vecteurs
	Vecteur& operator-=(Vecteur const& v); // soustraction de deux vecteurs
	Vecteur& operator^=(Vecteur const& autre); //Produit vectoriel
	Vecteur& operator*=(double a); // mult par un scalaire
	double operator*(Vecteur const& v); //produit scalaire
	Vecteur& operator/=(double a); //division par un scalaire
	bool operator==(Vecteur const& autre) const; //test d'egalite
	Vecteur operator-() const; //Vecteur opposé
	Vecteur operator~() const; //Vecteur unitaire

// Méthodes :
	void augmente(double valeur); // Ajoute une coordonnée au vecteur (ie une dimension) qui prend la valeur "valeur"
	void set_coord(std::size_t position, double valeur); // permet de modifier la coordonnée à la position "position" et en lui inculcant la valeur "valeur". La première coordonnées est à la position 0.
	std::ostream& affiche(std::ostream& out) const; // affiche le vecteur sous forme x1 x2 x3 x4 .....
	std::size_t dim() const; // renvoie la dimension du vecteur
	double norme() const; // renvoie la norme
	double norme2() const; // renvoie la norme au carré et permet d'éviter le temps de calcul de la racine
	double coeff(size_t x) const; // renvoie la coordonnée à la position x sachant que la première coordonnée est à la position x = 0
	void correctif_0(); //on l'utilise pour éviter d'avoir des valeurs extremement petites à la place de vrais 0 après certaines opérations.
    void modulo2pi();
private:
	// Attributs
	std::vector<double> coeff_;

};

// Opérateurs externes (prototypes)
const Vecteur operator+(Vecteur v, Vecteur const& w);
const Vecteur operator-(Vecteur v, Vecteur const& w);
const Vecteur operator*(Vecteur v, double a);
const Vecteur operator*(double a, Vecteur const& v);
const Vecteur operator/(Vecteur v, double a);
const Vecteur operator^(Vecteur v, Vecteur const& w);
std::ostream& operator<<(std::ostream& sortie, Vecteur const& vecteur);
