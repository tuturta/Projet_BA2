using namespace std;
#include <iostream>
#include "erreurs.h"
#include "Vecteur.h"
#include <cmath>
#include <string>

/// MÉTHODES
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
	out << ")";
	return out;
}
size_t Vecteur::dim() const {
	return coordonnees.size();
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

// DÉFINITIONS DES OPERATEURS:
// --> EXTERNES

ostream& operator<<(ostream& sortie, Vecteur const& vecteur) {
	return vecteur.affiche(sortie);
}
const Vecteur operator+(Vecteur v1, Vecteur const& v2) {
	v1+=v2;
	return v1;
}
const Vecteur operator*(Vecteur v, double a){
	v*=a;
	return v;
}
const Vecteur operator*(double a, Vecteur const& v) {
	return v*a;
}
const Vecteur operator/(Vecteur v, double a) {
	v/=a;
	return v;
}
const Vecteur operator-(Vecteur v, Vecteur const& w){
	v-= w;
	return v;
}
const Vecteur operator^(Vecteur v, Vecteur const& w){
	v ^= w;
	return v;
}

// --> INTERNES
Vecteur& Vecteur::operator+=(Vecteur const& autre){
	if (dim()!=autre.dim()) {
		Erreur Err = {"DIMENSIONS!",1};
		throw Err;
	}
	for (size_t i(0); i<dim(); ++i) {
			coordonnees[i]+=autre.coordonnees[i];
		}
		return *this;
}
double Vecteur::operator*(Vecteur const& autre){
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
Vecteur& Vecteur::operator*=(double a) {
	for (auto& i : coordonnees) {
		i*=a;
	}
	return *this;
}
Vecteur& Vecteur::operator/=(double a) {
	if ( a< 1e-8 ) {
		Erreur err={"Division par 0", 1};
		throw err;
	}
	return *this*=1/a;
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
Vecteur Vecteur::operator~() const{
	return (*this)/norme();
}
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
Vecteur Vecteur::operator-() const{
	Vecteur retour(dim());
	for(size_t i(0) ; i < dim() ; ++i){
		retour.coordonnees[i] = - coordonnees[i];
	}
	return retour;
}

