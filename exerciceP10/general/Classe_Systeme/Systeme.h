#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "../dessinable.h"
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../Classe_Integrateur/Integrateur.h"

class Systeme : public Dessinable{
   protected :
    std::vector<std::unique_ptr<Toupie>> objets; //classe hétérogène de Toupie(plus tard d'Intégrables)
    IntegrateurEulerCromer integrateur; // Integrateur propre au système
   public :
    Systeme(IntegrateurEulerCromer integrateur, SupportADessin* support) : Dessinable(support), integrateur(integrateur) {}
    void evolue(const double dt);
    //Pas de constructeur autre que par défaut pour le moment.
    void ajoute_toupie(Toupie const& nouvelle);
    std::ostream& affiche_parametres(std::ostream& out) const; //affiche l'ensemble des paramètres du système
    std::ostream& affiche(std::ostream& out) const; //ensemble le minimum necessaire pour dessine()
    virtual void dessine() override;

};

std::ostream& operator<<(std::ostream& out, Systeme const& S);
