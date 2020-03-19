using namespace std;
#include <iostream>
#include "erreurs.h"
#include "Vecteur.h"
#include <cmath>
#include <string>

/// MÉTHODES
void Vecteur::augmente(double valeur){
	coeff.push_back(valeur);
}
void Vecteur::set_coord(size_t position, double valeur){ 
	if (position<=dim()) {
		coeff[position-1]=valeur; ///Position 1=x,position 2=y, position 3=z
	}else{
		Erreur Err = {"DIMENSIONS!",1}; //Erreur de dim, code 1, niveau 1, n'arrette pas le programme
		throw Err;
	}
}
ostream& Vecteur::affiche(ostream& out) const {
	out << "( ";
	for(auto x : coeff) {
		out << x << " ";
	}
	out << ")";
	return out;
}
size_t Vecteur::dim() const {
	return coeff.size();
}
double Vecteur::norme() const {
	return sqrt(norme2());
}
double Vecteur::norme2() const{
	double retour;
	for(auto x : coeff) {
		retour += x*x;
	}
	return retour;
}
double Vecteur::coeff(size_t x) const {return coeff[x];}

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
			coeff[i]+=autre.coeff[i];
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
		x+=coeff[i]*autre.coeff[i];	
		}
		return x;
	}
}
Vecteur& Vecteur::operator*=(double a) {
	for (auto& i : coeff) {
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
		coeff[i] -= autre.coeff[i];
	}
	return *this;
}
Vecteur& Vecteur::operator^=(Vecteur const& autre){
	if(dim() != autre.dim() or dim() != 3) {
		Erreur Err = {"DIMENSIONS!",1};
		throw Err;
	}
	double temp0, temp1, temp2;
		temp0 = coeff[1]*autre.coeff[2]-coeff[2]*autre.coeff[1];
		temp1 = coeff[2]*autre.coeff[0]-coeff[0]*autre.coeff[2];
		temp2 = coeff[0]*autre.coeff[1]-coeff[1]*autre.coeff[0];
		coeff[0] = temp0;
		coeff[1] = temp1;
		coeff[2] = temp2;
		
		
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
		if(abs(coeff[i] - autre.coeff[i]) > 1e-8){
			retour = false;
		}
	}
	return retour;
}
Vecteur Vecteur::operator-() const{
	Vecteur retour(dim());
	for(size_t i(0) ; i < dim() ; ++i){
		retour.coeff[i] = - coeff[i];
	}
	return retour;
}

