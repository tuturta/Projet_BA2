#ifndef INTEGRABLE_H
#define INTEGRABLE_H

#include "../dessinable.h"
#include "../Classe_Vecteur/Vecteur.h"
#include "../support_a_dessin.h"
#include "../Classe_Matrice/Matrice.h"

class Integrable : public Dessinable{ // Car Un integrable est dessinable(on a ses paramètres à chaque pas de temps)
   protected : 
    Vecteur P; // Vecteur de paramètres psi-theta-phi
    Vecteur P_point; // Dérivée temporelle des degrés de liberté
    Vecteur point_de_contact;

   public:

    // CONSTRUCTEUR:

    Integrable(Vecteur P, Vecteur P_point, SupportADessin* support, Vecteur point_de_contact = {0,0,0})
        : Dessinable(support), P(P), P_point(P_point), point_de_contact(point_de_contact)  {}  // CONSTRUCTEUR PAR DEFAUT POUR LE SUPPORT ?
    

    // ACCESSEURS / SETTER

    Vecteur getP() const;
    Vecteur getP_point() const;
    Vecteur getPoint_de_conact() const;
    void setP(Vecteur const& autre);
    void setP_point(Vecteur const& autre);
    void setPoint_de_contact(Vecteur const& autre);


    // AFFICHAGE

    std::ostream& affiche(std::ostream& sortie) const;                     // Affiche seulement les angles d'euler, leur dérivée et le point de contact
    virtual std::ostream& affiche_parametres(std::ostream& out) const = 0; // Affiche tous les paramètres d'un intégrable avec du texte

    // MÉCANIQUE :

    virtual Vecteur fonction_f() const = 0;        // Equation du mouvement
    Vecteur ref_O_to_G(Vecteur const& vect) const; // Méthodes pour changer un vecteur de référentiel
    Vecteur ref_G_to_O(Vecteur const& vect) const; //
    virtual Vecteur ref_G_to_O_point(Vecteur const& point) const =0; // On veut obliger les toupies à avoir une méthode de changement de ref pour les points, mais on ne peut les définir qu'en connaissant leur CM

    Matrice S() const; // Matrice de transition de RG vers RO

};

#endif
