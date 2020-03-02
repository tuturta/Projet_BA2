#include <iostream>
#include "text_viewer.h"
#include "contenu.h"
using namespace std;

int main()
{
  /* Nous voulons un support à dessin :                          *
   * ici un TextViewer qui écrit sur cout                        */
  TextViewer ecran(cout);
  
  /* Nous voulons un contenu à dessiner, et que ce contenu       *
   * se dessine sur notre support à dessin précédent             */
  Contenu c(&ecran);

  // Nous dessinons notre contenu
  c.dessine();

  return 0;
}
