#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <exception>
#include "../../constantes.h"
#include "../../../text/text_viewer.h"
#include "../Integrable.h"
#include "../../Classe_Matrice/Matrice.h"
#include "../../Classe_Vecteur/Vecteur.h"
#include "../../support_a_dessin.h"
#include "../../erreurs.h"


// =============================== TOUPIE ==================================
enum Couleur {blanc, noir, rouge, jaune, bleu, vert, violet, orange};

class Toupie : public Integrable {     // Dans Toupie, le vecteur paramètre P est défini comme étant les angles d'Euler dans l'ordre (psi, theta, phi)

   // ATTRIBUTS PROTÉGÉS :

   protected : 
    double masse_volumique_;
    Vecteur point_de_contact_;          // Coordonnées du point de contact, actualisées à chaque évolution
    double hauteur_;                   // Hauteur du solide de révolution
    double rayon_;                     // Rayon de la base du cône / rayon de la sphère (tronquée)
    Couleur couleur_;
    std::vector<Vecteur> positions_CM; // Coordonnées du CM depuis le début de la simulation, dans le repère absolu

   // MÉTHODE PRIVÉE :

    double zi(size_t i) const;         // Donne la hauteur en fonction du découpage

   // CONSTRUCTION - COPIE -DESTRUCTION
   
   public :

    Toupie (Vecteur const& P, Vecteur const& P_point, double masse_volumique, Vecteur const& point_de_contact, double hauteur, double rayon, Couleur const& couleur = blanc, SupportADessin* support = new TextViewer(TextViewer(std::cout)))
        : Integrable(P, P_point, support), masse_volumique_(masse_volumique), point_de_contact_(point_de_contact), hauteur_(hauteur), rayon_(rayon), couleur_(couleur) {
            if ((hauteur < 0.0) or (rayon < eps) or (masse_volumique < eps)) {
                Erreur err = {"Votre objet doit avoir un sens physique!"};
                throw err; 
            }
        }

   // METHODES COMMUNES A TOUTES LES TOUPIES (INDEPENDANTES DE LA GEOMETRIE DE LA TOUPIE)

        // Grandeur physiques : publiques car l'utilisateur pourrait vouloir les utiliser
    Vecteur w() const;                          // vitesse angulaire (Ref O)
    Matrice matrice_inertie_A() const;          // Applique le théorème d'Huygens-Steiner pour translater la matrice d'inertie du point G au point A (en restant dans le ref G)
    Vecteur moment_poids() const;               // Moment du poids au point A
    Vecteur LA() const;                         // Moment d'inertie au point A (ref G)
    virtual Vecteur vecteurOG() const;                  // (ref O)
    
        
        // Invariants du mouvement: 
    double energie_totale() const;      // Énergie mécanique totale (invariant)
    double LAz() const;                 // Composante z du moment cinétique en A (Ref O) (invariant)
    double LA3() const;                 // Composante 3 du moment cinétique en A (Ref G) (invariant)
    double produitMixte_awL() const;    // Produit mixte a.(w^L) (invariant) 
    
        // Autres :  

   public  : 
    virtual std::unique_ptr<Toupie> copie() const =0;           // Copie polymorphique
    virtual std::ostream& affiche(std::ostream& sortie) const;   // Affichage des angles, dérivées et G
    virtual void dessine() = 0;                                  // Dessin lié au support   
    void update_A();                                             // Mise à jour du point de contact 
    Vecteur ref_G_to_O_point(Vecteur const& point)const override;// Changement de référentiel de G vers O
    void ajoute_position_CM();                                   // Pour garder en mémoire les positions du centre de masse
    std::vector<Vecteur> getPositions_CM() const;                // Accesseur des positions du centre de masse 
    double getHauteur() const;                                   // Accesseur pour la hauteur du cône/ hauteur tronquée des sphères tronquées   
    virtual double hauteur_toupie() const;                       // Renvoie la hauteur de la toupie depuis son point de contact
    double getRayon() const;                                     // Accesseur rayon du cône à sa base / sphère tronquée
    void setSupport(SupportADessin* nouveau_support);            // Permet de modifier le support dans le constructeur de GLWidget
    Couleur getColor() const;                                    // Renvoie la couleur de la toupie
    void setPoint_de_contact(Vecteur const& autre);
    Vecteur getPoint_de_contact() const;

    // MÉTHODES QUI DÉPENDENT DE LA GÉOMÉTRIE DE LA TOUPIE (--> MÉTHODES VIRTUELLES):

    virtual Matrice matrice_inertie_G() const;   // Matrice d'inertie en G (solide de révolution) (Ref G)

    virtual std::ostream& affiche_parametres(std::ostream& out) const override; // Affichage complet des paramètres d'une toupie
    
    virtual double masse() const;            // Masse d'un solide de révolution en fonction des rayons successifs + sa masse volumique  
    virtual double distanceBG() const;       // Distance 'origine de construction' du solide - centre de masse
    virtual Vecteur vecteurAG() const =0;    // (Ref G)
    virtual Vecteur vecteurOA() const =0;    // (Ref O)
    virtual Vecteur fonction_f() const = 0;  // Calcul des dérivées secondes 
   private :
    virtual double rayon2(size_t i) const=0; // Définit le solide de révolution : distance au carré à l'axe de révolution selon la hauteur zi. Doit être redéfini dans chaque classe

};

std::ostream& operator<<(std::ostream& sortie,Toupie const& toupie); // Surcharge d'opérateur (affichage)


// =============================== CONE GENERAL =================================== 
// But : retrouver un Cône Simple avec des méthodes plus générales

class ConeGeneral: public Toupie{   

   public: 

    // Constructeur plus adapté pour les graphismes : pas de support à apporter manuellement
    ConeGeneral(Vecteur const& P, Vecteur const& P_point, double masse_volumique, double hauteur, double rayon, Vecteur const& point_de_contact, Couleur const& couleur = blanc)
            : Toupie(P, P_point,masse_volumique,point_de_contact, hauteur,rayon, couleur)
            {
                if (hauteur < eps) {
                Erreur err = {"Un cône doit avoir une hauteur strictement positive!"};
                throw err;
                }
            }

    // Constructeur plus adapté aux parties textuelles : pas de couleur à fournir
    ConeGeneral(Vecteur const& P, Vecteur const& P_point, double masse_volumique, double hauteur, double rayon, Vecteur const& point_de_contact,SupportADessin* support = new TextViewer(TextViewer(std::cout)))
            : Toupie(P, P_point,masse_volumique,point_de_contact, hauteur,rayon, blanc, support) {
            if (hauteur < eps) {
                Erreur err = {"Un cône doit avoir une hauteur strictement positive!"};
                throw err;
            }
        }


   private :
    virtual double rayon2(size_t i) const override;  // Redéfinition pour un cône du rayon2 défini plus haut
    std::unique_ptr<ConeGeneral> clone() const;
   public :
    virtual std::unique_ptr<Toupie> copie() const override; // Copie polymorphique
    virtual Vecteur fonction_f() const override;            // Calcul général des dérivées secondes pour un cône
    virtual Vecteur vecteurAG() const override;             // (Ref G)
    virtual void dessine() override;
    virtual Vecteur vecteurOA() const override;           // (Ref O)
    virtual std::ostream& affiche_parametres(std::ostream& out) const override; // Affiche tous les paramètres d'une toupie


};

// ===============================CONE SIMPLE=======================================


class ConeSimple : public ConeGeneral {
   
   public: 

   // CONSTRUCTION - COPIE - DESTRUCTION

    using ConeGeneral::ConeGeneral;

   private :
    std::unique_ptr<ConeSimple> clone() const;
   public :
    virtual std::unique_ptr<Toupie> copie() const override; // Copie polymorphique

   // MÉCANIQUE - GÉOMÉTRIE DU SOLIDE

    virtual double masse() const override;
    virtual Matrice matrice_inertie_G() const override;  // Matrice d'inertie du cone simple en G (Ref G) 
    virtual Vecteur vecteurAG() const override;          // (Ref G)
    virtual Vecteur fonction_f() const override;         // Calcul spécifique des dérivées secondes pour un cône simple 

   // AFFICHAGE - DESSIN
    
    virtual std::ostream& affiche_parametres(std::ostream& out) const override; // Affiche tous les paramètres d'une toupie

};




// =============================== TOUPIE ROULANTE ===================================
// BUT : Retrouver une toupie chinoise avec une méthode plus générale


/*class ToupieRoulante: public Toupie{

    public:

    ToupieChinoiseGenerale(Vecteur param, Vecteur D_param, double masse_volumique, double hauteur, double rayon, Vecteur const& origine = {0,0,0}, SupportADessin* support = new TextViewer(TextViewer(std::cout)))
    :Toupie(param, D_param, masse_volumique, hauteur, rayon, origine, support){
        P.augmente(0.0);
        P.augmente(0.0);
        P.augmente(0.0);

        P_point.augmente(0.0); // Gx
        P_point.augmente(vecteurGC().norme()*sin(P.coeff(1))); // Gy
        P_point.augmente(getRayon()-vecteurGC().norme()*cos(P.coeff(1))); // Gz

    } // On ajoute les paramètres de la position du centre de masse : ce n'est pas à l'utilisateur de le faire. /!\ N'est adapté que pour retrouver une toupie chinoise  



};*/


class ToupieChinoiseGenerale: public Toupie{
   
   // CONSTRUCTION - COPIE - DESTRUCTION 
   
   public:


    // Constructeur plus adapté aux graphismes
    ToupieChinoiseGenerale(Vecteur param, Vecteur D_param, double masse_volumique, double hauteur, double rayon, Vecteur const& point_de_contact, Couleur const& couleur = blanc)
    :Toupie(param, D_param, masse_volumique,  point_de_contact, hauteur, rayon, couleur)
        {
            P.augmente(0.0);
            P.augmente(0.0);
            P.augmente(0.0);

            Vecteur AG(ref_G_to_O(vecteurAG()));  //On choisit d'utiliser ici d'appeler qu'une seule fois le vecteurAG() pour accélèrer la vitesse de calcul: chaque fois que la
                                  // méthode vecteurAG() est appelée, elle doit utiliser la méthode distanceBC() dans le cas génèrale (ie approché cette distance par des sommes)  
            P_point.augmente(point_de_contact.coeff(0) + AG.coeff(0)); // Gx
            P_point.augmente(point_de_contact.coeff(1) + AG.coeff(1)); // Gy
            P_point.augmente(point_de_contact.coeff(2) + AG.coeff(2)); // Gz
                

        } // On ajoute les paramètres de la position du centre de masse : ce n'est pas à l'utilisateur de le faire. /!\ N'est adapté que pour retrouver une toupie chinoise


    // Constructeur plus adapté au textuel
    ToupieChinoiseGenerale(Vecteur param, Vecteur D_param, double masse_volumique, double hauteur, double rayon, Vecteur const& point_de_contact, SupportADessin* support = new TextViewer(TextViewer(std::cout)))
        :Toupie(param, D_param, masse_volumique,  point_de_contact, hauteur, rayon, blanc, support)
        {
            P.augmente(0.0);
            P.augmente(0.0);
            P.augmente(0.0);
        
            Vecteur AG(ref_G_to_O(vecteurAG()));  //On choisit d'utiliser ici d'appeler qu'une seule fois le vecteurAG() pour accélèrer la vitesse de calcul: chaque fois que la
                                  // méthode vecteurAG() est appelée, elle doit utiliser la méthode distanceBC() dans le cas génèrale (ie approché cette distance par des sommes)  
            P_point.augmente(point_de_contact.coeff(0) + AG.coeff(0)); // Gx
            P_point.augmente(point_de_contact.coeff(1) + AG.coeff(1)); // Gy
            P_point.augmente(point_de_contact.coeff(2) + AG.coeff(2)); // Gz
                
        }


    virtual std::unique_ptr<Toupie> copie() const override; // Copie polymorphique

  private :
    std::unique_ptr<ToupieChinoiseGenerale> clone() const;

  // MÉCANIQUE - GÉOMÉTRIE :
  
  public :
    virtual Vecteur fonction_f() const override;     // Calcul général des dérivées secondes pour une toupie roulante
    virtual Vecteur vecteurAG() const override;      // (Ref G)
    virtual double rayon2(size_t i) const override;  // Redéfinition de rayon2 pour une toupie roulante
    virtual double hauteur_toupie() const override;  // Renvoie la hauteur totale d'une sphère et non sa hauteur tronquée
    virtual Vecteur vecteurGC() const;               // (Ref G) /!\ N'est adaptée qu'aux toupies chinoises
    virtual void dessine() override;
    virtual Vecteur  vecteurOA() const override;
    virtual Vecteur  vecteurOG() const override;
    Vecteur vecteurOC() const;
    // AFFICHAGE / DESSIN :
    virtual std::ostream& affiche(std::ostream& sortie) const override;
    virtual std::ostream& affiche_parametres(std::ostream& out) const override;

    };

// ===============================TOUPIE CHINOISE=====================================


class ToupieChinoise : public ToupieChinoiseGenerale{
    
  // CONSTRUCTION - COPIE - DESTRUCTION 

   public: 

    // Constructeur plus adapté pour les graphismes : pas de support à apporter manuellement
    ToupieChinoise(Vecteur param, Vecteur D_param, double masse_volumique, double hauteur, double rayon, Vecteur const& origine, Couleur const& couleur = blanc)
    : ToupieChinoiseGenerale(param, D_param, masse_volumique, hauteur, rayon, origine, couleur){
        P.pop_back(); // On enlève la 6ème dimension construite par toupie roulante
        P_point.pop_back();
        P_point.set_coord(3,origine.coeff(0)); // Cx
        P_point.set_coord(4,origine.coeff(1)); // Cy

    } // On a ajouté les paramètres de position du centre C


    // Constructeur plus adapté aux parties textuelles : pas de couleur à fournir
    ToupieChinoise(Vecteur param, Vecteur D_param, double masse_volumique, double hauteur, double rayon, Vecteur const& origine, SupportADessin* support = new TextViewer(TextViewer(std::cout)))
    : ToupieChinoiseGenerale(param, D_param, masse_volumique, hauteur, rayon, origine, support){
        P.pop_back(); // On enlève la 6ème dimension construite par toupie roulante
        P_point.pop_back();
        P_point.set_coord(3,origine.coeff(0)); // Cx
        P_point.set_coord(4,origine.coeff(1)); // Cy

    } // On a ajouté les paramètres de position du centre C
   
    virtual std::unique_ptr<Toupie> copie() const override; // Copie polymorphique
   private :
    std::unique_ptr<ToupieChinoise> clone() const;

   // MÉCANIQUE - GÉOMÉTRIE : 
   public :
    double alpha() const;                               // Voir figure de la sphère tronquée page 9 du complément mathématique
    virtual Vecteur vecteurGC() const override;                  // (Ref G)
    virtual double distanceBG() const override;                  // Distance origine de construction du solide de révolution - centre de masse (on la redéfinit pour avoir une valeur exacte et non approchée)
    virtual Vecteur vecteurOA() const override;                  // (Ref G)
    virtual double masse() const override;              // Redéfinie pour avoir des valeurs exactes et non approchées
    virtual Matrice matrice_inertie_G() const override; // Redéfinie pour avoir des valeurs exactes et non approchées
    virtual Vecteur fonction_f() const override;        // Calcul spécifique des dérivées secondes pour une toupie chinoise 
    virtual Vecteur vecteurOG() const override;

   // AFFICHAGE - DESSIN :
    virtual void dessine() override;
    virtual std::ostream& affiche_parametres(std::ostream& out) const override;

};
