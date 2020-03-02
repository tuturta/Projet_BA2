using namespace std;
#include <iostream>
#include "Vecteur.h"
#include <cmath>

void Vecteur::augmente(double valeur){
	coordonnees.push_back(valeur);
}
void Vecteur::set_coord(size_t position, double valeur){ // A FAIRE : Exception pour la dimension à la place du cout
	if (position<dim()) {
		coordonnees[position]=valeur;
	}else{
		cout << "la dimension du vecteur est trop petite. La coordonnee entree n existe pas"<<endl;
	}
}
void Vecteur::affiche() const {
	for(auto x : coordonnees) {
		cout << x << " ";
	}
	cout << endl;
}
bool Vecteur::compare(Vecteur v2) const { // A FAIRE : Lance une exception probleme de dimension
	if(dim() != v2.dim()) {
		return false;
	}
	size_t i(0);
	while(i < dim() and coordonnees[i]==v2.coordonnees[i]){
		++i;
	}
	if(i == dim()) {
		return true;
	}
	return false;
}
size_t Vecteur::dim() const {
	return coordonnees.size();
}
Vecteur Vecteur::addition(Vecteur autre) const { // A FAIRE : Lance une exception probleme de dimension
	Vecteur C;
	if (dim()==autre.dim()) {
		for (size_t i(0); i<dim();++i) {
			C.augmente(coordonnees[i]+autre.coordonnees[i]);
		}
	} else { 
		cerr << "DIMENSIONS DIFFERENTES!" << endl;
		C.augmente(0);
	}
	return C;
}
Vecteur Vecteur::oppose() const {
	Vecteur opp;
	for (auto i: coordonnees) {
		opp.augmente(-i);
	}
	return opp;
}
Vecteur Vecteur::soustraction(Vecteur autre) const { // A FAIRE : Lance une exception probleme de dimension
	return addition(autre.oppose());
}
Vecteur Vecteur::mult(double a) const {
	Vecteur C;
	for (size_t i(0); i<dim(); ++i) {
		
		C.augmente(coordonnees[i]*a);
	}
	return C;
}
double Vecteur::prod_scal(Vecteur autre) const { // A FAIRE: Lancer une exception si dimension non compatible
	double x;
	for (size_t i(0); i<dim(); ++i) {
		x+=coordonnees[i]*autre.coordonnees[i];	
	}
	return x;
 }	
Vecteur Vecteur::prod_vect(Vecteur autre) const{ // A FAIRE : Lance une exception probleme de dimension
	Vecteur C;
	if(dim() != autre.dim() or dim() != 3){
		C.augmente(0);
		cerr << "Problème de dimension"<<endl;
		return C;
	}
	C.augmente(coordonnees[1]*autre.coordonnees[2]-coordonnees[2]*autre.coordonnees[1]);
	C.augmente(coordonnees[2]*autre.coordonnees[0]-coordonnees[0]*autre.coordonnees[2]);
	C.augmente(coordonnees[0]*autre.coordonnees[1]-coordonnees[1]*autre.coordonnees[0]);
	return C;
}
double Vecteur::norme() const {
	return sqrt(norme2());
}
double Vecteur::norme2() const{
	double retour;
	for(auto x : coordonnees) {
		retour += x*x;
	}
	return retour;
}
Vecteur Vecteur::unitaire() const{
	Vecteur C;
	double a(1/norme()); // Calcul l'inverse de la norme. Evite de le calculer à chaque itération.
	for(auto x : coordonnees){
		C.augmente(a*x);
	}
	return C;
}
