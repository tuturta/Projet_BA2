#include <iostream>
#include "Systeme.h"
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../Classe_Integrateur/Integrateur.h"
#include "../support_a_dessin.h"
//#include "../Classe_Integrable/Integrable.h"



using namespace std;

ostream& Systeme::affiche_parametres(ostream& out) const {
    out << "Le système est constitué des " << objets.size() << " toupies suivantes :" << endl;
    for (size_t i(0); i<objets.size(); ++i) {
        if(objets[i]!=nullptr) {
            out << "=====Toupie " << i+1  << " :" << endl; 
            objets[i]->affiche_parametres(out);
            out << endl;
        }
    }
    return out;
}

ostream& operator<<(ostream& out, Systeme const& S) {
    return S.affiche_parametres(out);
} 


ostream& Systeme::affiche(ostream& out) const {
    unsigned int compteur(1);
    for(auto const& ptr_toupie : objets){
        if(ptr_toupie != nullptr){
            out << "[TOUPIE " << compteur << ']';
            ptr_toupie->affiche(out);
            ++compteur;
        }
    }
    return out;
}
    
void Systeme::ajoute_toupie(Toupie const& nouvelle){
    objets.push_back(nouvelle.copie());
}

/*unique_ptr<Integrable> Systeme::getObjets(size_t i) const{
    return objets[i]->copie(); //retourne une copie du pointeur du tableau pour pas que l'utilisateur puisse modifier la valeur pointée par celui_ci
}*/

/*void Systeme::setObjets(size_t i, Integrable const& autre){
    *objets[i] = autre;
}*/

size_t Systeme::size() const{return objets.size();}

void Systeme::dessine() {
    support->dessine(*this);
}

unique_ptr<Systeme> Systeme::clone() const{
    //return unique_ptr<Systeme>(new Systeme(*this));
    return nullptr; //POUR LES TESTS
}

//ESSAI ARTHUR *****************************************
/*unique_ptr<Dessinable> Systeme::copieDessinable() const {
   // return clone();
    return nullptr; //POUR LES TEST AUSSI
}*/

Toupie Systeme::getToupie(size_t i) const{
    return *objets[i];
}
void Systeme::setToupie(size_t i, Toupie const& autre){
    objets[i] = autre.copie();
}