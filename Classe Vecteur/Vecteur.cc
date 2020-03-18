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
ostream& Vecteur::affiche(ostream& out) const {
	out << "( ";
	for(auto x : coordonnees) {
		out << x << " ";
	}
	out << ")" << endl;
	return out;
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
	} 
	double x;
	for (size_t i(0); i<dim(); ++i) {
		x+=coordonnees[i]*autre.coordonnees[i];	
	}
	return x;
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


// DEFINITION DES OPERATEURS:

bool Vecteur::operator==(Vecteur const& autre) const{
	bool retour(true);
	if(dim() != autre.dim()) {
		Erreur Err = {"DIMENSIONS!", 1};
		throw Err;
	}
	for(size_t i(0) ; i < dim() ; ++i){
		if(abs(coordonnees[i] - autre.coordonnees[i]) > 1e-8){
			retour = false;
		}
	}
	return retour;
}

ostream& operator<<(ostream& sortie, Vecteur const& vecteur) {
	return vecteur.affiche(sortie);
}

Vecteur& Vecteur::operator-=(Vecteur const& autre){
	if(dim() != autre.dim()) {
		Erreur Err = {"DIMENSIONS!",1};
		throw Err;
	}
	for(size_t i(0) ; i<dim() ; ++i){
		coordonnees[i] -= autre.coordonnees[i];
	}
	return *this;
}

const Vecteur operator-(Vecteur v, Vecteur const& w){
	v-= w;
	return v;
}

Vecteur Vecteur::operator-() const{
	Vecteur retour(dim());
	for(size_t i(0) ; i<dim() ; ++i){
		if(coordonnees[i]>1e-8){retour.coordonnees[i] = -coordonnees[i];}
		}
	return retour;
}

Vecteur& Vecteur::operator^=(Vecteur const& autre){
	if(dim() != autre.dim() or dim() != 3) {
		Erreur Err = {"DIMENSIONS!",1};
		throw Err;
	}
	double temp0, temp1, temp2;
		temp0 = coordonnees[1]*autre.coordonnees[2]-coordonnees[2]*autre.coordonnees[1];
		temp1 = coordonnees[2]*autre.coordonnees[0]-coordonnees[0]*autre.coordonnees[2];
		temp2 = coordonnees[0]*autre.coordonnees[1]-coordonnees[1]*autre.coordonnees[0];
		coordonnees[0] = temp0;
		coordonnees[1] = temp1;
		coordonnees[2] = temp2;
		
		
		return *this;
}

const Vecteur operator^(Vecteur v, Vecteur const& w){
	v ^= w;
	return v;
}

Vecteur Vecteur::operator~() const{
	return (*this)/norme();
}