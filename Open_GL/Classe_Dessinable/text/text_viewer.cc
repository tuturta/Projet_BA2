#include <iostream> // pour endl
#include "text_viewer.h"

   void TextViewer::dessine(ConeSimple const& objet){
     objet.affiche(flot);
   }
   void TextViewer::dessine(Objet_en_chute_libre const& objet){
     objet.affiche(flot);
   }
   void TextViewer::dessine(Systeme const& objet){
     objet.affiche(flot);
   }

