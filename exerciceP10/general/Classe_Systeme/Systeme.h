#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "../dessinable.h"
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../Classe_Integrable/Integrable.h"
#include "../Classe_Integrateur/Integrateur.h"
#include "../../text/text_viewer.h"

class Systeme : public Dessinable {
   private :
    std::vector<std::unique_ptr<Toupie>> objets; // Classe hétérogène de Toupie(plus tard d'Intégrables)
    std::unique_ptr<Systeme> clone() const;

   public :

    // CONSTRUCTEUR :
    Systeme(SupportADessin* support = new TextViewer(TextViewer(std::cout))) : Dessinable(support) {}
    Systeme(Systeme const& autre) : Dessinable(autre.support) {
        for(auto const& nouvelle: autre.objets) {
            ajoute_toupie(*nouvelle);
        }
    }

    // MÉTHODES :

    void ajoute_toupie(Toupie const& nouvelle);
    std::ostream& affiche_parametres(std::ostream& out) const; // Affiche l'ensemble des paramètres du système
    std::ostream& affiche(std::ostream& out) const;
    virtual void dessine() override;
    std::unique_ptr<Toupie> getToupie(size_t i) const;
    void setToupie(size_t i, Toupie const& autre);
    double getHauteur(size_t i) const;
    double getRayon(size_t i) const;

    size_t size() const;  // nombre de toupies

};

std::ostream& operator<<(std::ostream& out, Systeme const& S);
