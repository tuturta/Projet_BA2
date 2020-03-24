#pragma once
#include "../Classe_Vecteur/Vecteur.h"
#include "../Classe_Integrateur/Integrateur.h"
#include "../Classe_Matrice/Matrice.h"

#include <iostream>

class Toupie {

   protected : 
    double masse_volumique; //Pour le moment, on le met dans la classe toupie car on ne connait pas la suite
    Vecteur P; // Vecteur de paramètres
    Vecteur P_point; // Dérivée temporelle des degrés de liberté
   
   public :
    Toupie (Vecteur const& P, Vecteur const& P_point, double masse_volumique) 
    : P(P), P_point(P_point), masse_volumique(masse_volumique) {} // Voir plus tard pour le corps : valeurs par défaut ? Message ?
    Vecteur fonction_f(); //Equation différentielles du mvt
    std::ostream& affiche(std::ostream& sortie) const;
    friend void Integrateur::evolue(Toupie& T, double dt) const;

};
std::ostream& operator<<(std::ostream& sortie,Toupie const& toupie);

//===============================================================================

class ConeSimple : public Toupie{
   
   private:
    double hauteur;
    double rayon;

   public: 
    ConeSimple(Vecteur const& P, Vecteur const& P_point, double masse_volumique, double hauteur, double rayon)
    : Toupie(P, P_point, masse_volumique), hauteur(hauteur), rayon(rayon) {}

    double masse() const;
    Matrice matrice_inertie() const; //Calcule le moment d'inertie I du cone simple
};


//================================================================================
class Objet_en_chute_libre : public Toupie {
   public:
    using Toupie::Toupie;
    Vecteur fonction_f() {
        return {0,-9.81};
    }

};