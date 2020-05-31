#ifndef INTEGRABLE_H
#define INTEGRABLE_H

#include "../dessinable.h"
#include "../Classe_Vecteur/Vecteur.h"
#include "../support_a_dessin.h"
#include "../Classe_Matrice/Matrice.h"

// =============== CLASSE INTEGRABLE =================(Abstraite)

class Integrable : public Dessinable{ // Un intégrable est dessinable ( On a ses paramètres à chaque pas de temps, donc on peut dessiner le mouvement d'un point )
   
   // ATTRIBUTS : 
   
   protected : 
    Vecteur P;                // Paramètres psi-theta-phi + autres paramètres supplémentaires si plus de 3 degrés de liberté
    Vecteur P_point;          // Dérivée temporelle des degrés de liberté
    Vecteur point_de_contact_;          // Coordonnées du point de contact, actualisées à chaque évolution
    std::vector<Vecteur> positions_CM; // Coordonnées du CM depuis le début de la simulation, dans le repère absolu


   // CONSTRUCTEUR - DESTRUCTEUR

   public:
    Integrable(Vecteur const& P, Vecteur const& P_point, Vecteur const& point_de_contact, SupportADessin* support) : Dessinable(support), P(P), P_point(P_point), point_de_contact_(point_de_contact) {}
   // MANIPULATEURS :

    Vecteur getP() const;
    Vecteur getP_point() const;
    void setP(Vecteur const& autre);
    void setP_point(Vecteur const& autre);
    void ajoute_position_CM();   // Pour garder en mémoire les positions du centre de masse
    std::vector<Vecteur> getPositions_CM() const;                // Accesseur des positions du centre de masse 
    void update_A();                                             // Mise à jour du point de contact 
    void setPoint_de_contact(Vecteur const& autre);              // Méthode pour l'utilisateur   
    Vecteur getPoint_de_contact() const;
    
    // AFFICHAGE

    std::ostream& affiche(std::ostream& sortie) const;                     // Affiche seulement les angles d'euler, et leur dérivées
    virtual std::ostream& affiche_parametres(std::ostream& out) const = 0; // Affichage complet des paramètres : il faut que chaque toupie puisse fournir ces données

    // MÉCANIQUE :
    virtual Vecteur vecteurOG() const =0;
    virtual Vecteur vecteurOA() const =0;
    virtual Vecteur fonction_f() const = 0;                          // Calcul des dérivées secondes : chaque toupie à géométrie connue doit fournir un résultat adapté
    Vecteur ref_O_to_G(Vecteur const& vect) const;                   // Changement de référentiel, O vers G (pour les Vecteurs)
    Vecteur ref_G_to_O(Vecteur const& vect) const;                   // Changement de référentiel, G vers O (pour les Vecteurs)
    virtual Vecteur ref_G_to_O_point(Vecteur const& point) const =0; // Changement de référentiel, G vers O, (Points) : chaque toupie à géométrie connue doit fournir cette méthode

    Matrice S() const; // Matrice de transition de Ref G vers Ref O

};



// ============================= Objet en chute libre ======================================


class Objet_en_chute_libre : public Integrable {

   public:   
    using Integrable::Integrable;
    virtual Vecteur fonction_f() const override;
    virtual Vecteur ref_G_to_O_point(Vecteur const& point) const override;
    virtual Vecteur vecteurOG() const override;
    virtual Vecteur vecteurOA() const override;
    virtual std::ostream& affiche_parametres(std::ostream& out) const override;
    virtual void dessine() override;
    std::ostream& affiche(std::ostream& sortie) const;  // Surcharge pour des raisons pratiques dans testIntegrateur (gnuplot)
   
};

std::ostream& operator<<(std::ostream& sortie,Objet_en_chute_libre const& objet); // Surcharge d'opérateur (affichage)






#endif
