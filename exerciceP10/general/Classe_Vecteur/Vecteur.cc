#define _USE_MATH_DEFINES //Pour régler le problème de M_PI non reconnu par le compilateur sur windows
#include <iostream>
#include "../erreurs.h"
#include "../constantes.h"
#include "Vecteur.h"

#include <cmath>
#include <string>
using namespace std;

// MÉTHODES

void Vecteur::augmente(double valeur){
	coeff_.push_back(valeur);
}

void Vecteur::pop_back() {
    coeff_.pop_back();
}

void Vecteur::set_coord(size_t position, double valeur){ 
	if (position<=dim()) {
        coeff_[position]=valeur; /// Position 0 = x ou psi, position 1 = y ou theta, position 2 = z ou phi
	}else{
                Erreur Err = {"DIMENSIONS ! (set_coord)"};
		throw Err;
	}
}
ostream& Vecteur::affiche(ostream& out) const {
	out << "( ";
	for(auto x : coeff_) {
		out << x << " ";
	}
	out << ")";
	return out;
}
size_t Vecteur::dim() const {
	return coeff_.size();
}
double Vecteur::norme() const {
	return sqrt(norme2());
}
double Vecteur::norme2() const{
    double retour(0);
	for(auto x : coeff_) {
		retour += x*x;
	}
	return retour;
}
double Vecteur::coeff(size_t x) const {
	if(dim()<x){
		Erreur err = {"Vous cherchez à avoir accès au coeff "+to_string(x)+" d'un vecteur de dimension "+to_string(dim())+"!"};
		throw err;
	}
	return coeff_[x];
	}

void Vecteur::correctif_0() {
	 for (auto& c: coeff_) {
		 if (abs(c)<=eps) {
			 c=0.0;
		 }
	 }
 }

void Vecteur::modulo2pi(size_t i) {
    if(coeff(i)>=2.0*M_PI) {
			   coeff_[i] -= 2.0*M_PI*floor(coeff(i)/(2.0*M_PI));
	}else if(coeff(i)<0.0){
			   coeff_[i] += 2.0*M_PI*(floor(-coeff(i)/(2.0*M_PI))+1.0);
		   }
     // pour obtenir les angles modulo 2 pi
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
                Erreur Err = {"DIMENONS! (op+=)"};
		throw Err;
	}
	for (size_t i(0); i<dim(); ++i) {
			coeff_[i]+=autre.coeff_[i];
		}
		correctif_0();
	return *this;
}
double Vecteur::operator*(Vecteur const& autre){
	if(dim()!=autre.dim()) {
                Erreur Err= {"DIMENSIONS! (op*)"};
		throw Err;
	} else {
        double x(0);
		for (size_t i(0); i<dim(); ++i) {
		x+=coeff_[i]*autre.coeff_[i];	
		}
		return x;
	}
}
Vecteur& Vecteur::operator*=(double a) {
	for (auto& i : coeff_) {
		i*=a;
	}
	correctif_0(); //vérifier
	return *this;
}
Vecteur& Vecteur::operator/=(double a) {
	if ( a< 1e-8 ) {
                Erreur err={"Division par 0"};
		throw err;
	}
	return *this*=1/a;
}
Vecteur& Vecteur::operator-=(Vecteur const& autre){
	if(dim() != autre.dim()) {
                Erreur Err = {"DIMENONS! (op-=)"};
		throw Err;
	}
	for(size_t i(0) ; i<dim() ; ++i){
		coeff_[i] -= autre.coeff_[i];
	}
	correctif_0();
	return *this;
}
Vecteur& Vecteur::operator^=(Vecteur const& autre){
	if(dim() != autre.dim() or dim() != 3) {
                Erreur Err = {"DIMENONS! (op^=)"};
		throw Err;
	}
	double temp0, temp1, temp2;
	temp0 = coeff_[1]*autre.coeff_[2]-coeff_[2]*autre.coeff_[1];
	temp1 = coeff_[2]*autre.coeff_[0]-coeff_[0]*autre.coeff_[2];
	temp2 = coeff_[0]*autre.coeff_[1]-coeff_[1]*autre.coeff_[0];
	coeff_[0] = temp0;
	coeff_[1] = temp1;
	coeff_[2] = temp2;
		
	correctif_0();	
	return *this;
}
Vecteur Vecteur::operator~() const{
	return (*this)/norme();
}
bool Vecteur::operator==(Vecteur const& autre) const{
	bool retour(true);
	if(dim() != autre.dim()) {
                Erreur Err = {"DIMENTIONS! (op==)"};
		throw Err;
	}
	for(size_t i(0) ; i < dim() ; ++i){
		if(abs(coeff_[i] - autre.coeff_[i]) > eps){
			retour = false;
		}
	}
	return retour;
}
Vecteur Vecteur::operator-() const{
	Vecteur retour(dim());
	for(size_t i(0) ; i < dim() ; ++i){
		retour.coeff_[i] = - coeff_[i];
	}
	return retour;
}

