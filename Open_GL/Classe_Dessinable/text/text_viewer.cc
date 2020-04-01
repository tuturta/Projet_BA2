#include <iostream> // pour endl
#include "text_viewer.h"
#include "../general/contenu.h"

void TextViewer::dessine(Contenu const& a_dessiner)
{
  flot << a_dessiner.infos() << std::endl;
}
