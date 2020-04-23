#ifndef SUPPORT_A_DESSIN_H
#define SUPPORT_A_DESSIN_H


class ConeSimple;
class Objet_en_chute_libre;
class Toupie;
class Systeme;

class SupportADessin {
   public :
    virtual ~SupportADessin() {}
  
   // Mettre ici toutes les méthodes pour dessiner tous les objets que l'on veut dessiner :
   virtual void dessine(ConeSimple const& objet) =0;
   virtual void dessine(Objet_en_chute_libre const& objet) =0;
   virtual void dessine(Toupie const& objet) =0;
   virtual void dessine(Systeme const& objet) =0;

   //....
};

#endif

