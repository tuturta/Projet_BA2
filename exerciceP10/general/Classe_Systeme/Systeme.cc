#include <iostream>
#include "Systeme.h"
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../Classe_Integrateur/Integrateur.h"
#include "../support_a_dessin.h"
#include "../Classe_Integrable/Integrable.h"



using namespace std;

ostream& Systeme::affiche_parametres(ostream& out) const {
    out << "Le système est constitué des " << objets.size() << " toupies suivantes :" << endl;
    for (size_t i(0); i<objets.size(); ++i) {
        if(objets[i]!=nullptr) {
            out << "===== Toupie " << i+1  << " :" << endl; 
            objets[i]->affiche_parametres(out);
            out << endl;
        }
    }
    return out;
}

ostream& operator<<(ostream& out, Systeme const& S) {
    return S.affiche_parametres(out);
} 


ostream& Systeme::affiche(ostream& out) const {  //PAS SUR QUE CA SOIT UTILE
    unsigned int compteur(1);
    for(auto const& ptr_toupie : objets){
        if(ptr_toupie != nullptr){
            out << "[TOUPIE " << compteur << ']' << endl ;
            ptr_toupie->affiche(out);
            ++compteur;
        }
    }
    return out;
}
    
void Systeme::ajoute_toupie(Toupie const& nouvelle){
    objets.push_back(nouvelle.copie());
}

size_t Systeme::size() const{ return objets.size(); }

void Systeme::dessine() {

    unsigned int compteur(1);
    for (auto const& ptr_toupie : objets){
        if(ptr_toupie != nullptr){
            ptr_toupie->dessine();
            ++compteur;
        }
        else{
            // ERREUR NULLPTR
        }
    } 
}

unique_ptr<Systeme> Systeme::clone() const{
    //return unique_ptr<Systeme>(new Systeme(*this));
    return nullptr; //POUR LES TESTS
}

unique_ptr<Toupie> Systeme::getToupie(size_t i) const{
    return objets[i]->copie();
}
void Systeme::setToupie(size_t i, Toupie const& autre){    
    *objets[i] = autre;
}
double Systeme::getHauteur(size_t i) const{
    return objets[i]->getHauteur();
}
double Systeme::getRayon(size_t i) const{
    return objets[i]->getRayon();
}

void Systeme::setSupport(SupportADessin* nouveau_support) {
    support = nouveau_support;
    for(auto const& ptr_toupie : objets){
        ptr_toupie->setSupport(nouveau_support);
    }
}

void Systeme::evolue(const double dt) {
    for(auto const& ptr_toupie : objets) {
        integrateur->evolue(*ptr_toupie, dt);
    }
}
