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

    std::vector<std::unique_ptr<Toupie>> objets; //classe hétérogène de Toupie(plus tard d'Intégrables)
    std::unique_ptr<Systeme> clone() const;
   public :
    Systeme(SupportADessin* support = new TextViewer(TextViewer(std::cout))) : Dessinable(support) {}
    Systeme(Systeme const& autre) : Dessinable(autre.support) {
        for(auto const& nouvelle: autre.objets) {
            ajoute_toupie(*nouvelle);
        }
    }
    void ajoute_toupie(Toupie const& nouvelle);
    std::ostream& affiche_parametres(std::ostream& out) const; //affiche l'ensemble des paramètres du système
    std::ostream& affiche(std::ostream& out) const; //ensemble le minimum necessaire pour dessine()
    virtual void dessine() override;
    // std::unique_ptr<Integrable> getObjets(size_t i) const; //Accéde à la ieme toupie du systeme (0 etant la premiere)
    //void setObjets(size_t i, Integrable const& autre); //Modifie la ieme toupie du systeme (0 etant la premiere) en la remplaçant par "autre"
    std::unique_ptr<Toupie> getToupie(size_t i) const;
    void setToupie(size_t i, Toupie const& autre);
    double getHauteur(size_t i) const;
    double getRayon(size_t i) const;
    Toupie getT (size_t i) const {return *objets[i];}
    size_t size() const;
    //virtual std::unique_ptr<Dessinable> copieDessinable() const override;

};

std::ostream& operator<<(std::ostream& out, Systeme const& S);
