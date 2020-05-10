#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include "../../../text/text_viewer.h"
#include "../Integrable.h"
#include "../../Classe_Matrice/Matrice.h"
#include "../../Classe_Vecteur/Vecteur.h"
#include "../../support_a_dessin.h"


class Toupie : public Integrable {

   protected : 
    double masse_volumique;
    std::vector<Vecteur> positions_CM; // il s'agit des coordonnées du CM depuis le début de la simulation, dans le repère absolu
   public :
    Toupie (Vecteur const& P, Vecteur const& P_point, double masse_volumique, Vecteur const& origine = {0,0,0}, SupportADessin* support = new TextViewer(TextViewer(std::cout)))
        : Integrable(P, P_point, support, origine), masse_volumique(masse_volumique) {} //pourquoi ne doit-on pas initialiser positions_CM ?? bizarre

    virtual std::ostream& affiche_parametres(std::ostream& out) const override;
    //A terme, toupie sera certainement une classe virtuelle : on ne permet donc pas de la dessiner pour l'instant
    virtual Vecteur fonction_f() const override; //à terme  =0; ?
    virtual std::unique_ptr<Toupie> copie() const; // A terme, Integrable à la place de Toupie
    std::unique_ptr<Toupie> clone() const;

    virtual void dessine() override;

    virtual double getHauteur() const; // pour l'instant
    virtual double getRayon() const; // Pour l'instant
    void ajoute_position_CM();
    std::vector<Vecteur> getPositions_CM() const;
    virtual Vecteur ref_G_to_O_point(Vecteur const& point) const override;

};
std::ostream& operator<<(std::ostream& sortie,Toupie const& toupie);

//===============================================================================

class ConeSimple : public Toupie{
   
   private:
    double hauteur;
    double rayon;
   public: 

    // CONSTRUCTION - COPIE - DESTRUCTION

    ConeSimple(Vecteur const& P, Vecteur const& P_point, double masse_volumique, double hauteur, double rayon, Vecteur const origine, SupportADessin* support = new TextViewer(TextViewer(std::cout)))
    : Toupie(P, P_point, masse_volumique, origine, support), hauteur(hauteur), rayon(rayon) {} // COnstructeur qui initialise l'origine à 0,0,0
    virtual std::ostream& affiche_parametres(std::ostream& out) const override; // Affiche tous les paramètres d'une toupie

    std::unique_ptr<ConeSimple> clone() const;
    virtual std::unique_ptr<Toupie> copie() const override; // A terme, Integrable à la place de Toupie

    //****Destructeur ?

    // MÉCANIQUE - GÉOMÉTRIE DU SOLIDE

    double masse() const;
    Matrice matrice_inertie() const; //Calcule le moment d'inertie I du cone simple
    Vecteur moment_poids() const;
    Vecteur vecteurAG() const;
    virtual Vecteur ref_G_to_O_point(Vecteur const& point) const override;
    virtual Vecteur fonction_f() const override;

    // ACCESSEURS

    virtual double getHauteur() const override;
    virtual double getRayon() const override;

    // AFFICHAGE - DESSIN

    virtual void dessine() override;

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

    virtual double getHauteur() const override;
    virtual double getRayon() const override;
};
