#ifndef INTEGRABLE_H
#define INTEGRABLE_H

#include "../dessinable.h"
#include "../Classe_Vecteur/Vecteur.h"
#include "../support_a_dessin.h"
#include "../Classe_Matrice/Matrice.h"

class Integrable : public Dessinable{ // Car Un integrable est dessinable(on a ses paramètres à chaque pas de temps)
   protected : 
    Vecteur P; // Vecteur de paramètres
    Vecteur P_point; // Dérivée temporelle des degrés de liberté
    Vecteur origine;

   public:
    //METHODES:
    Integrable(Vecteur P, Vecteur P_point, SupportADessin* support, Vecteur origine = {0,0,0})
    : Dessinable(support), P(P), P_point(P_point), origine(origine)  {} //CONSTRUCTEUR PAR DEFAUT POUR LE SUPPORT
    
    virtual Vecteur fonction_f() const = 0; //Equation du mouvement
    Vecteur getP() const;
    Vecteur getP_point() const;
    void setP(Vecteur const& autre);
    void setP_point(Vecteur const& autre);
    std::ostream& affiche(std::ostream& sortie) const; // Affiche seulement P et Ppoint
    void ref_O_to_G(Vecteur&) const; //méthodes pour changer un vecteur de référentiel *************************************
    void ref_G_to_O(Vecteur&) const; // ************************************************************************************
    Matrice S() const; // Matrice de transition de RG vers RO *********A METTRE DANS CETTE CLASSE OU NON ?************

};

#endif