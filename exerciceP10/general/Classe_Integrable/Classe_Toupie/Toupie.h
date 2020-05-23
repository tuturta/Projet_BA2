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


class Toupie : public Integrable {     // Dans Toupie, le vecteur paramètre P est défini comme étant les angles d'Euler dans l'ordre (psi, theta, phi)

   protected : 
    std::vector<Vecteur> positions_CM; // il s'agit des coordonnées du CM depuis le début de la simulation, dans le repère absolu
    double masse_volumique;
    double hauteur_;                   // hauteur du solide de révolution
    double rayon_;                     // Rayon de la base du cône / rayon de la sphère (tronquée)

    double zi(size_t i) const;         // Donne la hauteur en fonction du découpage
    virtual double rayon2(size_t i) const; //c'est ce qui défini le solide de révolution : c'est la distance au carré à l'axe ri en fonction de la hauteur zi. Il doit être redefini dans chaque classe --> A TRANSFORMER EN VIRTUELLE PURE

   public :
    Toupie (Vecteur const& P, Vecteur const& P_point, double masse_volumique, double hauteur, double rayon, Vecteur const& point_de_contact = {0,0,0}, SupportADessin* support = new TextViewer(TextViewer(std::cout)))
        : Integrable(P, P_point, support, point_de_contact), masse_volumique(masse_volumique),hauteur_(hauteur), rayon_(rayon) {}

    virtual std::ostream& affiche_parametres(std::ostream& out) const override;
    //A terme, toupie sera certainement une classe virtuelle : on ne permet donc pas de la dessiner pour l'instant
    virtual Vecteur fonction_f() const override;
    virtual std::unique_ptr<Toupie> copie() const;
    std::unique_ptr<Toupie> clone() const;
    Vecteur w() const;
    virtual double getHauteur() const;
    virtual double getRayon() const; // Pour l'instant
    void ajoute_position_CM();
    std::vector<Vecteur> getPositions_CM() const;
    virtual Vecteur ref_G_to_O_point(Vecteur const& point) const override; 
    virtual void dessine() override;


    //METHODES POUR LE CAS GENERAL
    double distanceBG() const; // retourne la distance entre l'origine du solide de révolution et son centre de masse 
    virtual Vecteur vecteurAG() const;
    double masse() const;
    Matrice matrice_inertie() const; //Calcul la matrice d'inertie du solide de révolution dans le repère d'inertie et au point A 



};

std::ostream& operator<<(std::ostream& sortie,Toupie const& toupie);


//===============================CONE GENERAL===============================================

class ConeGeneral: public Toupie{                   // Cone simple avec la fonction génèrale !
   public: 
    using Toupie :: Toupie;                         // Constructeur du cone simple
    virtual double rayon2(size_t i) const override; // C'est ce qui défini le solide de révolution : c'est la distance à l'axe ri en fonction de la hauteur zi
    virtual Vecteur fonction_f() const override;
    virtual Vecteur vecteurAG() const override;
    std::unique_ptr<ConeGeneral> clone() const;
    virtual std::unique_ptr<Toupie> copie() const override;
};

//===============================CONE SIMPLE=================================================


class ConeSimple : public ConeGeneral {
   
   public: 

    // CONSTRUCTION - COPIE - DESTRUCTION

    ConeSimple(Vecteur const& P, Vecteur const& P_point, double masse_volumique, double hauteur, double rayon, Vecteur const& point_de_contact, SupportADessin* support = new TextViewer(TextViewer(std::cout)))
    : ConeGeneral(P, P_point, masse_volumique, hauteur, rayon, point_de_contact, support) {} // COnstructeur qui initialise l'origine à 0,0,0
    virtual std::ostream& affiche_parametres(std::ostream& out) const override; // Affiche tous les paramètres d'une toupie

    std::unique_ptr<ConeSimple> clone() const;
    virtual std::unique_ptr<Toupie> copie() const override;

    //****Destructeur ?

    // MÉCANIQUE - GÉOMÉTRIE DU SOLIDE

    double masse() const;
    Matrice matrice_inertie() const;            //Calcule le moment d'inertie I du cone simple au point de contact
    Vecteur moment_poids() const;
    virtual Vecteur vecteurAG() const override; //Dans RefG
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


//=============================Objet en chute libre======================================


class Objet_en_chute_libre : public Toupie {
   private:
    std::unique_ptr<Objet_en_chute_libre> clone() const;
   public:   
    using Toupie::Toupie;
    virtual Vecteur fonction_f() const override;
    virtual void dessine() override;
    virtual std::unique_ptr<Toupie> copie() const override;
    virtual double getHauteur() const override;
    virtual double getRayon() const override;
};



//===============================TOUPIE Roulante==================================================

class ToupieRoulante: public Toupie{ // Cone simple avec la fonction génèrale !
   public: 
    ToupieRoulante(Vecteur P, Vecteur P_point, double masse_volumique, double hauteur, double rayon, Vecteur const& origine = {0,0,0}, SupportADessin* support = new TextViewer(TextViewer(std::cout)))
    :Toupie(P,  P_point,    masse_volumique,    hauteur,    rayon,origine,  support){}
    
    virtual Vecteur fonction_f() const override;
    virtual Vecteur vecteurAG() const override;
    virtual double rayon2(size_t i) const override; //c'est ce qui défini le solide de révolution : c'est la distance à l'axe ri en fonction de la hauteur zi
    std::unique_ptr<ToupieRoulante> clone() const;
    virtual std::unique_ptr<Toupie> copie() const override; // A terme, Integrable à la place de Toupie
    Vecteur vecteurGC() const; //Retourne le vecteur GC DANS LE REF G
    Vecteur vecteurOB() const; //vecteur entre l'origine du solide de révolution et l'origine du repère galiléen (REF O). Methode utile pour QtGL
};

//===============================TOUPIE CHINOISE==================================================


class ToupieChinoise : public ToupieRoulante{ //Cas spécifique de toupie roulante
   public: 
    using ToupieRoulante::ToupieRoulante ; // Attention, ici la hauteur est en réalité h (cf p9): c'est la hauteur tranquée à la sphère de rayon R et non la hauteur de la toupie 
   
    Matrice matrice_inertie() const; //Calcul la matrice d'inertie dans le repère d'inertie ET AU POINT G
    virtual Vecteur fonction_f() const override;
    double masse() const; 
    double alpha() const; // Cf fiigure de la sphère tronquée p9 du complément mathématique
    Vecteur vecteurGC() const; //Retourne le vecteur GC DANS LE REF G
    std::unique_ptr<ToupieChinoise> clone() const;
    virtual std::unique_ptr<Toupie> copie() const override; // A terme, Integrable à la place de Toupie


};
