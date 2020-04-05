#include <iostream> // pour endl
#include "text_viewer.h"
#include "../../../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../../../Classe_Systeme/Systeme.h"

   void TextViewer::dessine(ConeSimple const& objet){
     flot << objet << std::endl;
   }
   void TextViewer::dessine(Objet_en_chute_libre const& objet){
     flot << objet << std::endl;
   }
   void TextViewer::dessine(Toupie const& objet){
     flot << objet << std::endl;
   } 
  void TextViewer::dessine(Systeme const& objet) {
    flot << objet << std::endl;
  }
