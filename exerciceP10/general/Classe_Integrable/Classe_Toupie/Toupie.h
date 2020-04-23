#pragma once
#include <iostream>
#include <memory>
#include <cmath>
#include "../../../text/text_viewer.h"
#include "../Integrable.h"
#include "../../Classe_Matrice/Matrice.h"
#include "../../Classe_Vecteur/Vecteur.h"
#include "../../support_a_dessin.h"


class Toupie : public Integrable {

   protected : 
    double masse_volumique; //Pour le moment, on le met dans la classe toupie car on ne connait pas la suite
    
   
   public :
    Toupie (Vecteur const& P, Vecteur const& P_point, double masse_volumique, SupportADessin* support, Vecteur const& origine = {0,0,0}) 
    : Integrable(P, P_point, support, origine), masse_volumique(masse_volumique) {} // Voir plus tard pour le corps : valeurs par défaut ? Message ?
    /*si on doit bien initialiser origine avec la pos d'origine */

    

    virtual std::ostream& affiche_parametres(std::ostream& out) const; // Affiche tous les paramètres d'une toupie 
    ///A terme, toupie sera certainement une classe virtuelle : on ne permet donc pas de la dessiner pour l'instant
    virtual Vecteur fonction_f() const override;
    std::unique_ptr<Toupie> clone() const;
    virtual std::unique_ptr<Toupie> copie() const; // A terme, Integrable à la place de Toupie
    virtual void dessine() override;

};
std::ostream& operator<<(std::ostream& sortie,Toupie const& toupie);

//===============================================================================

class ConeSimple : public Toupie{
   
   private:
    double hauteur;
    double rayon;

   public: 
    ConeSimple(Vecteur const& P, Vecteur const& P_point, double masse_volumique, SupportADessin* support, double hauteur, double rayon, Vecteur const origine)
    : Toupie(P, P_point, masse_volumique, support, origine), hauteur(hauteur), rayon(rayon) {} // COnstructeur qui initialise l'origine à 0,0,0
    virtual std::ostream& affiche_parametres(std::ostream& out) const override; // Affiche tous les paramètres d'une toupie
    double masse() const;
    Matrice matrice_inertie() const; //Calcule le moment d'inertie I du cone simple
    Vecteur moment_poids() const;
    Vecteur centre_de_masse() const;

    virtual Vecteur fonction_f() const override;
    virtual void dessine() override;
    
    std::unique_ptr<ConeSimple> clone() const;
    virtual std::unique_ptr<Toupie> copie() const; // A terme, Integrable à la place de Toupie

    //getter pour les attributs nécéssités par dessineToupie
    double getHauteur() const;
    double getRayon() const;
};


//================================================================================
class Objet_en_chute_libre : public Toupie {
   public:
    using Toupie::Toupie;
    virtual Vecteur fonction_f() const override;
    virtual void dessine() override;
    std::unique_ptr<Objet_en_chute_libre> clone() const;
    virtual std::unique_ptr<Toupie> copie() const; // A terme, Integrable à la place de Toupie
};
