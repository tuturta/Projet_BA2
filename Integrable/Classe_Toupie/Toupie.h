#pragma once

#include <iostream>
#include <memory>
//#include "../Classe_Vecteur/Vecteur.h"
//#include "../Classe_Matrice/Matrice.h"
//#include "../Open_GL/Classe_Dessinable/general/dessinable.h"
//#include "../Classe_Integrateur/Integrateur.h"


class Toupie : public Dessinable {

   protected : 
    Vecteur P; // Vecteur de paramètres
    Vecteur P_point; // Dérivée temporelle des degrés de liberté
    double masse_volumique; //Pour le moment, on le met dans la classe toupie car on ne connait pas la suite
    Vecteur origine; //*****pour l'instant aucune autre info dessus...******
   public :
    Toupie (unique_ptr<SupportADessin> support, Vecteur const& P, Vecteur const& P_point, double masse_volumique) 
    : Dessinable(move(support)), P(P), P_point(P_point), masse_volumique(masse_volumique), origine(P) {} // Voir plus tard pour le corps : valeurs par défaut ? Message ?
    /*si on doit bien initialiser origine avec la pos d'origine */
    virtual Vecteur fonction_f() const = 0; //Equation différentielles du mvt
    
    std::ostream& affiche(std::ostream& sortie) const;
    
    virtual std::ostream& affiche_parametres(std::ostream& out) const;

    Vecteur getP() const;
    Vecteur getP_point() const;
    void setP(Vecteur const& autre);
    void setP_point(Vecteur const& autre);
    ///A terme, toupie sera certainement une classe virtuelle : on ne permet donc pas de la dessiner pour l'instant
};
std::ostream& operator<<(std::ostream& sortie,Toupie const& toupie);

//===============================================================================

class ConeSimple : public Toupie{
   
   private:
    double hauteur;
    double rayon;

   public: 
    ConeSimple(unique_ptr<SupportADessin> support, Vecteur const& P, Vecteur const& P_point, double masse_volumique, double hauteur, double rayon)
    : Toupie(move(support),P, P_point, masse_volumique), hauteur(hauteur), rayon(rayon) {}
    virtual std::ostream& affiche_parametres(std::ostream& out) const override;
    double masse() const;
    Matrice matrice_inertie() const; //Calcule le moment d'inertie I du cone simple
    virtual Vecteur fonction_f() const override;
    virtual void dessine() override;
};


//================================================================================
class Objet_en_chute_libre : public Toupie {
   public:
    using Toupie::Toupie;
    virtual Vecteur fonction_f() const override;

    virtual void dessine() override;
};