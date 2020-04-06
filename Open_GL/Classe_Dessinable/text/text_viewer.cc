#include <iostream> // pour endl
#include "text_viewer.h"
#include "../../../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../../../Classe_Systeme/Systeme.h"
#include "../../../Classe_Integrable/Integrable.h"

   void TextViewer::dessine(ConeSimple const& objet){
     objet.affiche(flot);
   }
   void TextViewer::dessine(Objet_en_chute_libre const& objet){
     objet.affiche(flot);
   }
   void TextViewer::dessine(Toupie const& objet){
     objet.affiche(flot);
   } 
  void TextViewer::dessine(Systeme const& objet) {
    objet.affiche(flot);
  }
