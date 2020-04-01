#ifndef SUPPORT_A_DESSIN_H
#define SUPPORT_A_DESSIN_H
#include "../../../Classe_Toupie/Toupie.h"
#include "../../../Classe_Systeme/Systeme.h"


class Contenu;

class SupportADessin {
   public :
    virtual ~SupportADessin() {}
    virtual void dessine(Contenu const& a_dessiner) =0;
    /* Mettre ici toutes les méthodes pour dessiner tous les objets que l'on veut dessiner par exemple:
    *   virtual void dessine(Nounours const& a_dessiner) = 0;
    *   virtual void dessine(Voiture consz& a_dessiner) = 0;
    */
   virtual void dessine(ConeSimple const&) =0;
   virtual void dessine(Systeme const&) = 0;
   //....
};

#endif;