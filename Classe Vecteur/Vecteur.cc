using namespace std;
#include <iostream>
#include "erreurs.h"
#include "Vecteur.h"
#include <cmath>
#include <string>

void Vecteur::augmente(double valeur){
	coordonnees.push_back(valeur);
}
void Vecteur::set_coord(size_t position, double valeur){ 
	if (position<=dim()) {
		coordonnees[position-1]=valeur; ///Position 1=x,position 2=y, position 3=z
	}else{
		Erreur Err = {"DIMENSIONS!",1}; //Erreur de dim, code 1, niveau 1, n'arrette pas le programme
		throw Err;
	}
}
void Vecteur::affiche() const {
	cout << "(";
	for(auto x : coordonnees) {
		cout << x << " ";
	}
	cout << ")" << endl;
}
bool Vecteur::compare(Vecteur v2) const {
	if(dim() != v2.dim()) {
		Erreur Err = {"DIMENSIONS!", 1};
		throw Err;
	}
	size_t i(0);
	while(i < dim() and coordonnees[i]==v2.coordonnees[i]){
		++i;
	}
	if(i == dim()) {
		return true;
	} else {
		return false;
	}
}
size_t Vecteur::dim() const {
	return coordonnees.size();
}
Vecteur Vecteur::addition(Vecteur autre) const {
	Vecteur C(0);
	if (dim()==autre.dim()) {
		for (size_t i(0); i<dim();++i) {
			C.augmente(coordonnees[i]+autre.coordonnees[i]);
		}
		return C;
	} else { 
		Erreur Err = {"DIMENSIONS!",1};
		throw Err;
	}
}
Vecteur Vecteur::oppose() const {
	Vecteur opp(0);
	for (auto i: coordonnees) {
		opp.augmente(-i);
	}
	return opp;
}
Vecteur Vecteur::soustraction(Vecteur autre) const { // A FAIRE : Lance une exception probleme de dimension --> fait par addition
	return addition(autre.oppose());
}
Vecteur Vecteur::mult(double a) const {
	Vecteur C(0);
	for (size_t i(0); i<dim(); ++i) {
		C.augmente(coordonnees[i]*a);
	}
	return C;
}
double Vecteur::prod_scal(Vecteur autre) const { 
	if(dim()!=autre.dim()) {
		Erreur Err= {"DIMENSIONS!",1};
		throw Err;
	} else {
		double x;
		for (size_t i(0); i<dim(); ++i) {
		x+=coordonnees[i]*autre.coordonnees[i];	
		}
		return x;
	}
 }	
Vecteur Vecteur::prod_vect(Vecteur autre) const{
	Vecteur C(0);
	if(dim() != autre.dim()) {
		Erreur Err = {"DIMENSIONS!",1};
		throw Err;
	} else if (dim()!=3) {
		Erreur Err = {"Poduit vectoriel non défini entre ces vecturs!",1};
		throw Err;
	} else {
		C.augmente(coordonnees[1]*autre.coordonnees[2]-coordonnees[2]*autre.coordonnees[1]);
		C.augmente(coordonnees[2]*autre.coordonnees[0]-coordonnees[0]*autre.coordonnees[2]);
		C.augmente(coordonnees[0]*autre.coordonnees[1]-coordonnees[1]*autre.coordonnees[0]);
		return C;
	}
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
	Vecteur C(0);
	double a(1/norme()); // Calcul l'inverse de la norme. Evite de le calculer à chaque itération.
	for(auto x : coordonnees){
		C.augmente(a*x);
	}
	return C;
}
