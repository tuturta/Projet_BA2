#include <vector>


class Vecteur 
{
public:
//Constructeur (par défaut il construit un vecteur nul en 3 dimensions)
	Vecteur(std::vector<double> coordonnees = {0.0,0.0,0.0}): coordonnees(coordonnees) {}
//Méthodes
	void augmente(double valeur); // Ajoute une coordonnée au vecteur (ie une dimension) qui prend la valeur "valeur"
	void set_coord(std::size_t position, double valeur); // permet de modifier la coordonnée à la position "position" et en lui inculcant la valeur "valeur". La première coordonnées est à la position 0.
	void affiche() const; // affiche le vecteur sous forme x1 x2 x3 x4 .....
	bool compare(Vecteur v2) const; //
	std::size_t dim() const; // renvoie la dimension du vecteur
	Vecteur oppose() const; // renvoie le vecteur unitaire
	Vecteur addition(Vecteur autre) const; // additionne 2 vecteurs
	Vecteur soustraction(Vecteur autre) const; // soustrait 2 vecteurs
	Vecteur mult(double a) const; // multiplie par le scalaire "a" le vecteur
	double prod_scal(Vecteur autre) const; // produit scalaire avec le vecteur "autre"
	Vecteur prod_vect(Vecteur autre) const; // produit vectorielle avec le vecteur "autre" 
	double norme() const; // renvoie la norme
	double norme2() const; // renvoie la norme au carré et permet d'éviter le temps de calcul de la racine
	Vecteur unitaire() const; // renvoie le vecteur unitaire (ie. même sens et même direction mais de norme 1)
	
//Attributs:
private:
	std::vector<double> coordonnees;
	
};


