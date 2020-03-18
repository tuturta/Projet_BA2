#include <vector>
#include <initializer_list>
#include <cmath>
#include <iostream>

class Vecteur 
{
public:
// Constructeurs
	Vecteur(double x, double y, double z): coordonnees({x,y,z}) {} //vecteur 3D
	Vecteur(size_t dim) : coordonnees(dim,0.0) {} //Vecteur nul de la dimension voulue
	Vecteur (std::initializer_list<double> const& list) { 
		for (auto i : list) { coordonnees.push_back(i);} 
	}
	Vecteur (double r, double theta, double phi, bool sph) { //TEST COORD SPHERIQUES (A SUPPRIMER) POURQUOI POSERAIT-IL PROBLEME? 
		coordonnees.push_back(r*sin(theta)*cos(phi));
		coordonnees.push_back(r*sin(theta)*sin(phi));
		coordonnees.push_back(r*cos(theta));
	}
// Opérateurs internes (prototypes)
	Vecteur& operator+=(Vecteur const& v);
	Vecteur& operator-=(Vecteur const& v);
	Vecteur& operator*=(double a); // mult par un scalaire
	double operator*(Vecteur const& v); //produit scalaire
	Vecteur& operator/=(double a);
	Vecteur& operator-();
	bool operator==(Vecteur const& autre) const;
// Méthodes
	void augmente(double valeur); // Ajoute une coordonnée au vecteur (ie une dimension) qui prend la valeur "valeur"
	void set_coord(std::size_t position, double valeur); // permet de modifier la coordonnée à la position "position" et en lui inculcant la valeur "valeur". La première coordonnées est à la position 0.
	std::ostream& affiche(std::ostream& out) const; // affiche le vecteur sous forme x1 x2 x3 x4 .....
	std::size_t dim() const; // renvoie la dimension du vecteur
	double norme() const; // renvoie la norme
	double norme2() const; // renvoie la norme au carré et permet d'éviter le temps de calcul de la racine
	Vecteur unitaire() const; // renvoie le vecteur unitaire (ie. même sens et même direction mais de norme 1)
	Vecteur prod_vect(Vecteur autre) const;
// Attributs:
private:
	std::vector<double> coordonnees;
	
};

// Opérateurs externes (prototypes)
const Vecteur operator+(Vecteur v, Vecteur const& w);
const Vecteur operator-(Vecteur v, Vecteur const& w);
const Vecteur operator*(Vecteur v, double a);
const Vecteur operator*(double a, Vecteur const& v);
const Vecteur operator/(Vecteur v, double a);
std::ostream& operator<<(std::ostream& sortie, Vecteur const& vecteur);
