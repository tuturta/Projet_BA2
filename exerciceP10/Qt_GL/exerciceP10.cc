#include <QApplication>
#include <iostream>
#include "glwidget.h"
#include "../general/Classe_Vecteur/Vecteur.h"
#include "../general/Classe_Integrable/Classe_Toupie/Toupie.h"

int main(int argc, char* argv[])
{
ConeSimple cone1({0.523599,0.0,0.0},{0.0,0.0,60.0},0.1,1.5,0.5,{0.0,0.0,0.0});
ConeSimple cone2({0.785398, 0.0,0.0}, {0,0.0,40.0} ,0.1, 1.5, 0.5, {0.1,0.0,0.0});
Systeme systeme;
systeme.ajoute_toupie(cone1);
systeme.ajoute_toupie(cone2);
  QApplication a(argc, argv);
  GLWidget w(systeme); //A adapter pour un systeme
  w.show();
  return a.exec();
}
