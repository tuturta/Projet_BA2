#pragma once
#include <iostream>
#include <memory>
//#include "../Classe_Vecteur/Vecteur.h"
#include "../../Classe_Matrice/Matrice.h"
#include "../Integrable.h"


class Toupie : public Integrable {

   protected : 
    double masse_volumique; //Pour le moment, on le met dans la classe toupie car on ne connait pas la suite
   
   public :
    Toupie (Vecteur const& P, Vecteur const& P_point, double masse_volumique, Vecteur const& origine = {0,0,0}) 
    : Integrable(P, P_point, origine), masse_volumique(masse_volumique) {} // Voir plus tard pour le corps : valeurs par défaut ? Message ?
    /*si on doit bien initialiser origine avec la pos d'origine */
    
    std::ostream& affiche(std::ostream& sortie) const;
    virtual std::ostream& affiche_parametres(std::ostream& out) const;
    ///A terme, toupie sera certainement une classe virtuelle : on ne permet donc pas de la dessiner pour l'instant

    unique_ptr<Toupie> clone() const;
    virtual unique_ptr<Integrable> copie() const;

};
std::ostream& operator<<(std::ostream& sortie,Toupie const& toupie);

//===============================================================================

class ConeSimple : public Toupie{
   
   private:
    double hauteur;
    double rayon;

   public: 
    ConeSimple(Vecteur const& P, Vecteur const& P_point, double masse_volumique, double hauteur, double rayon)
    : Toupie(P, P_point, masse_volumique), hauteur(hauteur), rayon(rayon) {} // COnstructeur qui initialise l'origine à 0,0,0
    virtual std::ostream& affiche_parametres(std::ostream& out) const override;
    double masse() const;
    Matrice matrice_inertie() const; //Calcule le moment d'inertie I du cone simple
    virtual Vecteur fonction_f() const override;
    virtual void dessine() override;
    
    unique_ptr<ConeSimple> clone() const;
    virtual unique_ptr<Integrable> copie() const;

};


//================================================================================
class Objet_en_chute_libre : public Toupie {
   public:
    using Toupie::Toupie;
    virtual Vecteur fonction_f() const override;
    virtual void dessine() override;
};