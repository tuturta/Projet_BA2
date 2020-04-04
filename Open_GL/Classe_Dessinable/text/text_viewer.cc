#include <iostream> // pour endl
#include "text_viewer.h"

   void TextViewer::dessine(ConeSimple const& objet){
     flot << objet << std::endl;
   }
   void TextViewer::dessine(Objet_en_chute_libre const& objet){
     flot << objet << std::endl;
   }
   void TextViewer::dessine(Systeme const& objet){
     flot << objet << std::endl;
   }

