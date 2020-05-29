#include <iostream> // pour endl
#include "text_viewer.h"
#include "../general/Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../general/Classe_Integrable/Integrable.h"

   void TextViewer::dessine(ConeGeneral const& objet){
     objet.affiche(flot);
   }
   void TextViewer::dessine(Objet_en_chute_libre const& objet){
     objet.affiche(flot);
   }
   void TextViewer::dessine(Toupie const& objet){
     objet.affiche(flot);
   } 
   void TextViewer::dessine(ToupieChinoiseGenerale const& objet) {
       objet.affiche(flot);
     }


