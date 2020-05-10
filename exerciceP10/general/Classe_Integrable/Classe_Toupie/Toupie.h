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


class Toupie : public Integrable { // Dans Toupie, le vecteur paramètre P est défini comme étant les angles d'Euler dans l'ordre (psi, theta, phi)

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
    Vecteur w() const;

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
   
   protected:
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
    Vecteur vecteurAG() const; //Dans RefG
    Vecteur w() const;
    virtual Vecteur fonction_f() const override;
    virtual double getHauteur() const override;
    virtual double getRayon() const override;
    virtual Vecteur ref_G_to_O_point(Vecteur const& point) const override;
    //MECANIQUE - INVARIANTS DU MOUVEMENT

    double energie_totale() const;      //Energie mécanique totale du cone : c'est un invariant
    double LAz() const;                 // Composante z du moment cinétique au point A exprimé dans le référentiel galliléen O : c'est un invariant
    double LA3() const;                 // Composante 3 du moment cinétique au point A exprimé dans le référentiel inertiel G : c'est un invariant
    double produitMixte_awL() const;    //Produit mixte a.(w^L) : c'est un invariant   
    
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

//================================================================================

class ConeGeneral: public ConeSimple{ // Cone simple avec la fonction génèrale !
   public: 
    using ConeSimple :: ConeSimple; // COnstructeur du cone simple
    virtual Vecteur fonction_f() const override;
    Matrice matrice_inertie() const; //matrice d'inertie dans le repère G au point G
    Vecteur vecteurAG() const;
    double masse() const;
    std::unique_ptr<ConeGeneral> clone() const;
    virtual std::unique_ptr<Toupie> copie() const override; // A terme, Integrable à la place de Toupie

};

