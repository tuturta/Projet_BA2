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

   public :
    Toupie (Vecteur const& P, Vecteur const& P_point, double masse_volumique, double hauteur, double rayon, Vecteur const& point_de_contact = {0,0,0}, SupportADessin* support = new TextViewer(TextViewer(std::cout)))
        : Integrable(P, P_point, support, point_de_contact), masse_volumique(masse_volumique),hauteur_(hauteur), rayon_(rayon) {}


    //METHODES COMMUNES A TOUTES LES TOUPIES (INDEPENDANTES DE LA GEOMETRIE DE LA TOUPIE)

        //Grandeur physiques: 
    Vecteur ref_G_to_O_point(Vecteur const& point) const; 
    Vecteur w() const;                          // Ref O
    Matrice matrice_inertie_A() const;          //Applique le théorème d'Huygens-Steiner pour translater la matrice d'inertie du point G au point A (en restant dans le ref G)
    Vecteur moment_poids() const;               //Calcul le moment du poids au point A
    Vecteur LA() const;                         // Renvoie le moment d'inertie au point A dans le ref G
    Vecteur vecteurOG() const;                  // Défini à partir de OA et AG, dans le ref O
    
        
        //Invariants du mouvement: 
    double energie_totale() const;      //Energie mécanique totale du cone : c'est un invariant
    double LAz() const;                 // Composante z du moment cinétique au point A exprimé dans le référentiel galliléen O : c'est un invariant
    double LA3() const;                 // Composante 3 du moment cinétique au point A exprimé dans le référentiel inertiel G : c'est un invariant
    double produitMixte_awL() const;    //Produit mixte a.(w^L) : c'est un invariant   
    
        //Autres:
    virtual std::unique_ptr<Toupie> copie() const;
    std::unique_ptr<Toupie> clone() const;
    virtual void dessine() override;
    void update_A(); // Mise à jour du point de contact 
    double getHauteur() const;
    double getRayon() const;                    
    void ajoute_position_CM();
    std::vector<Vecteur> getPositions_CM() const;
    std::ostream& affiche(std::ostream& sortie) const;

    // METHODES QUI DEPEND DE LA GEOMETRIE DE LA TOUPIE (--> METHODES VIRTUELLES):

    virtual Matrice matrice_inertie_G() const; //Calcul la matrice d'inertie du solide de révolution dans le repère d'inertie et au centre de masse G
    virtual double rayon2(size_t i) const; //c'est ce qui défini le solide de révolution : c'est la distance au carré à l'axe ri en fonction de la hauteur zi. Il doit être redefini dans chaque classe --> A TRANSFORMER EN VIRTUELLE PURE
    virtual Vecteur vecteurAG() const;      //Dans le ref A
    virtual Vecteur vecteurOA() const;      //Dans le ref O
    virtual Vecteur fonction_f() const override;
    virtual std::ostream& affiche_parametres(std::ostream& out) const override;
    virtual double masse() const;
    virtual double distanceBG() const; // retourne la distance entre l'origine du solide de révolution et son centre de masse


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
    
    std::unique_ptr<ConeSimple> clone() const;
    virtual std::unique_ptr<Toupie> copie() const override;

    // MÉCANIQUE - GÉOMÉTRIE DU SOLIDE

    virtual double masse() const override;
    virtual Matrice matrice_inertie_G() const override;           //Calcul la matrice d'inertie du cone simple dans le repère d'inertie et au centre de masse G 
    virtual Vecteur vecteurAG() const override; //Dans RefG
    virtual Vecteur fonction_f() const override;

    // AFFICHAGE - DESSIN
    
    virtual std::ostream& affiche_parametres(std::ostream& out) const override; // Affiche tous les paramètres d'une toupie
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
   
};



//===============================TOUPIE ROULANTE==================================================

class ToupieRoulante: public Toupie{ // Cone simple avec la fonction génèrale !
   public: 
    ToupieRoulante(Vecteur param, Vecteur D_param, double masse_volumique, double hauteur, double rayon, Vecteur const& origine = {0,0,0}, SupportADessin* support = new TextViewer(TextViewer(std::cout)))
    :Toupie(param,  D_param,    masse_volumique,    hauteur,    rayon,origine,  support){
        P.augmente(0.0);
        P.augmente(0.0);
        P.augmente(0.0);

        P_point.augmente(0.0); //Gx
        P_point.augmente(vecteurGC().norme()*sin(P.coeff(1))); //Gy
        P_point.augmente(getRayon()-vecteurGC().norme()*cos(P.coeff(1))); //Gz

    } //on ajoute les paramètres de la position du centre de masse : ce n'est pas à l'utilisateur de le faire. /!\ TOUPIE CHINOISE UNIQUEMENT
    
    virtual Vecteur fonction_f() const override;
    virtual Vecteur vecteurAG() const override;
    virtual double rayon2(size_t i) const override; //c'est ce qui défini le solide de révolution : c'est la distance à l'axe ri en fonction de la hauteur zi
    virtual Vecteur vecteurGC() const; //Retourne le vecteur GC dans le ref G /!\ N'est adaptée qu'aux toupies chinoises
    void update_A(); //méthode pour mettre à jour la position du point de contact /!\ N'est adaptée qu'aux toupies chinoises, la méthode générale étant considérée trop ambitieuse pour ce projet

    std::unique_ptr<ToupieRoulante> clone() const;
    virtual std::unique_ptr<Toupie> copie() const override; // A terme, Integrable à la place de Toupie?

    // AFFICHAGE / DESSIN :

    virtual std::ostream& affiche_parametres(std::ostream& out) const override;
    };

//===============================TOUPIE CHINOISE==================================================


class ToupieChinoise : public ToupieRoulante{ //Cas spécifique de toupie roulante
   public: 

    ToupieChinoise(Vecteur param, Vecteur D_param, double masse_volumique, double hauteur, double rayon, Vecteur const& origine = {0,0,0}, SupportADessin* support = new TextViewer(TextViewer(std::cout)))
    : ToupieRoulante(param, D_param, masse_volumique, hauteur, rayon,origine, support){
        P.pop_back(); // on enlève la 6ème dimension construite par toupie roulante
        P_point.pop_back();
        P_point.set_coord(3,0.0); // Cx
        P_point.set_coord(4,0.0); // Cy

    } // On ajoute les paramètres de position du centre C
   
    virtual Vecteur fonction_f() const override;
    virtual double masse() const override; 
    double alpha() const; // Cf fiigure de la sphère tronquée p9 du complément mathématique
    virtual Vecteur vecteurGC() const; //Retourne le vecteur GC DANS LE REF G
    std::unique_ptr<ToupieChinoise> clone() const;
    virtual std::unique_ptr<Toupie> copie() const override; // A terme, Integrable à la place de Toupie
    virtual Matrice matrice_inertie_G() const override; //Calcul la matrice d'inertie dans le repère d'inertie ET AU POINT G

    // AFFICHAGE / DESSIN :

    virtual std::ostream& affiche_parametres(std::ostream& out) const override;
    std::ostream& affiche(std::ostream& sortie) const;
    virtual void dessine() override;

    virtual double distanceBG() const; // retourne la distance entre l'origine du solide de révolution et son centre de masse
    virtual Vecteur vecteurOA() const;      //Dans le ref O

};
