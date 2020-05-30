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


   // CONSTRUCTEUR :

   public:
    Integrable(Vecteur P, Vecteur P_point, SupportADessin* support)
        : Dessinable(support), P(P), P_point(P_point)  {}

   // MANIPULATEURS :

    Vecteur getP() const;
    Vecteur getP_point() const;
    void setP(Vecteur const& autre);
    void setP_point(Vecteur const& autre);


    // AFFICHAGE

    std::ostream& affiche(std::ostream& sortie) const;                     // Affiche seulement les angles d'euler, leur dérivée et le point de contact
    virtual std::ostream& affiche_parametres(std::ostream& out) const = 0; // Affichage complet des paramètres : il faut que chaque toupie puisse fournir ces données

    // MÉCANIQUE :

    virtual Vecteur fonction_f() const = 0;                          // Calcul des dérivées secondes : chaque toupie à géométrie connue doit fournir un résultat adapté
    Vecteur ref_O_to_G(Vecteur const& vect) const;                   // Changement de référentiel, O vers G (pour les Vecteurs)
    Vecteur ref_G_to_O(Vecteur const& vect) const;                   // Changement de référentiel, G vers O (pour les Vecteurs)
    virtual Vecteur ref_G_to_O_point(Vecteur const& point) const =0; // Changement de référentiel, G vers O, (Points) : chaque toupie à géométrie connue doit fournir cette méthode

    Matrice S() const; // Matrice de transition de Ref G vers Ref O

};



// =============================Objet en chute libre======================================


class Objet_en_chute_libre : public Integrable {
   private:
    //std::unique_ptr<Objet_en_chute_libre> clone() const;
   public:   
    using Integrable::Integrable;
    virtual Vecteur fonction_f() const override;
    virtual void dessine() override;
    //virtual std::unique_ptr<Toupie> copie() const; // Copie polymorphique
   
};






#endif
