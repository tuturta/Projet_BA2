#ifndef SUPPORT_A_DESSIN_H
#define SUPPORT_A_DESSIN_H

#include <iostream>

class ConeGeneral;
class ConeSimple;
class Objet_en_chute_libre;
class Toupie;
class ToupieRoulante;
class ToupieChinoiseGenerale;

class SupportADessin {
   public :
    virtual ~SupportADessin() { std::cout << "Destructeur virtuel de SupportADessin" << std::endl; }
  
    // Toutes les méthodes pour dessiner tous les objets que l'on veut dessiner :
    virtual void dessine(ConeGeneral const& objet) =0;
    virtual void dessine(ToupieChinoiseGenerale const& objet) =0;
    virtual void dessine(Objet_en_chute_libre const& objet) =0;
    virtual void dessine(Toupie const& objet) =0;

};

#endif

