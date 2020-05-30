#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "../erreurs.h"
#include "../dessinable.h"
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../Classe_Integrable/Integrable.h"
#include "../Classe_Integrateur/Integrateur.h"
#include "../../text/text_viewer.h"
#include <memory>

class Systeme : public Dessinable {
  
   // ATTRIBUTS :
  
   private :
    std::vector<std::unique_ptr<Toupie>> objets; // Classe hétérogène de Toupies
    std::unique_ptr<Integrateur> integrateur;    // Car Integrateur est une classe abstraite

   // CONSTRUCTION - COPIE - DESTRUCTION

      /* L'utilisation de unique_ptr nous décharge de la désallocation de mémoire :
       * le destructeur par défaut convient */

   public :
    Systeme(Integrateur* integ, SupportADessin* support = new TextViewer(TextViewer(std::cout))) : Dessinable(support), integrateur((*integ).copie()) {
        if (integrateur==nullptr) {
            Erreur err ={"L'intégrateur doit déjà exister à la construction"};
            throw err;
        }
    } // Construction d'un système vide, puis on lui ajoute des éléments
    
    Systeme(Systeme const& autre) : Dessinable(autre.support), integrateur((autre.integrateur)->copie()) {
        for(auto const& nouvelle: autre.objets) {
            ajoute_toupie(*nouvelle);
        }
    } // Copie de système : avec copie profonde pour les pointeurs


   // MÉTHODES :

   private :
    void test_numero(size_t i) const;                          // Teste si la toupie du numéro passé en argument existe
   public :
    void evolue(const double dt);                              // Faire évoluer les toupies du système avec l'integrateur choisi
    void ajoute_toupie(Toupie const& nouvelle);                // Ajout d'un nouvel élément au système
    std::ostream& affiche_parametres(std::ostream& out) const; // Affiche l'ensemble des paramètres du système
    std::ostream& affiche(std::ostream& out) const;            // Affichage plus succin
    virtual void dessine() override;                           // Dessine selon le support
    std::unique_ptr<Toupie> getToupie(size_t i) const;         // Accesseur de l'élément i de 'objets'
    void setToupie(size_t i, Toupie const& autre);             // Setter de l'élement i de 'objets' 
    double getHauteur(size_t i) const;                         // Hauteur de l'élément i de 'objets' 
    double getRayon(size_t i) const;                           // Rayon de l'élément i de 'objets'
    size_t size() const;                                       // Nombre d'objets dans le système 
    void setSupport(SupportADessin* nouveau_support);          // Permet de modifier le support dans le constructeur de GLWidget
   
};

std::ostream& operator<<(std::ostream& out, Systeme const& S);
