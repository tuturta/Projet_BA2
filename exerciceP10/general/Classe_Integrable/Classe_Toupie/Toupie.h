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
    double masse_volumique;
    std::unique_ptr<Toupie> clone() const;

   
   public :
    Toupie (Vecteur const& P, Vecteur const& P_point, double masse_volumique, Vecteur const& origine = {0,0,0}, SupportADessin* support = new TextViewer(TextViewer(std::cout)))
    : Integrable(P, P_point, support, origine), masse_volumique(masse_volumique) {} // Voir plus tard pour le corps : valeurs par défaut ? Message ?

    virtual std::ostream& affiche_parametres(std::ostream& out) const override;
    //A terme, toupie sera certainement une classe virtuelle : on ne permet donc pas de la dessiner pour l'instant
    virtual Vecteur fonction_f() const override; //à terme  =0; ?
    virtual std::unique_ptr<Toupie> copie() const; // A terme, Integrable à la place de Toupie

    //virtual std::unique_ptr<Dessinable> copieDessinable() const override; // Pour GLwidget, necessite d'un retour covariant des sous classes de dessinable

    virtual void dessine() override;

    virtual double getHauteur() const=0;
    virtual double getRayon() const=0;
};
std::ostream& operator<<(std::ostream& sortie,Toupie const& toupie);

//===============================================================================

class ConeSimple : public Toupie{
   
   private:
    double hauteur;
    double rayon;
    std::unique_ptr<ConeSimple> clone() const;
   public: 
    ConeSimple(Vecteur const& P, Vecteur const& P_point, double masse_volumique, double hauteur, double rayon, Vecteur const origine, SupportADessin* support = new TextViewer(TextViewer(std::cout)))
    : Toupie(P, P_point, masse_volumique, origine, support), hauteur(hauteur), rayon(rayon) {} // COnstructeur qui initialise l'origine à 0,0,0
    virtual std::ostream& affiche_parametres(std::ostream& out) const override; // Affiche tous les paramètres d'une toupie
    double masse() const;
    Matrice matrice_inertie() const; //Calcule le moment d'inertie I du cone simple
    Vecteur moment_poids() const;
    Vecteur centre_de_masse() const;

    virtual double getHauteur() const override;
    virtual double getRayon() const override;

    virtual Vecteur fonction_f() const override;
    virtual void dessine() override;
    

    virtual std::unique_ptr<Toupie> copie() const override; // A terme, Integrable à la place de Toupie

    //ESSAI ARTHUR *****************************************
    //virtual std::unique_ptr<Dessinable> copieDessinable() const override; // Pour GLwidget, necessite d'un retour covariant des sous classes de dessinable
};


//================================================================================
class Objet_en_chute_libre : public Toupie {
   private:
    std::unique_ptr<Objet_en_chute_libre> clone() const;
   public:   
    using Toupie::Toupie;
    virtual Vecteur fonction_f() const override;
    virtual void dessine() override;
    virtual std::unique_ptr<Toupie> copie() const override; // A terme, Integrable à la place de Toupie

    //ESSAI ARTHUR *****************************************
    //virtual std::unique_ptr<Dessinable> copieDessinable() const override; // Pour GLwidget, necessite d'un retour covariant des sous classes de dessinable
    virtual double getHauteur() const override;
    virtual double getRayon() const override;
};
