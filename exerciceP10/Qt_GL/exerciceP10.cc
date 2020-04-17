#include <QApplication>
#include <iostream>
#include "glwidget.h"
#include "../general/Classe_Vecteur/Vecteur.h"

int main(int argc, char* argv[])
{
  Vecteur P({0.523599,0.0,0.0});
  Vecteur P_point({0.0,0.0,60.0});
  Vecteur origine({0.0,0.0,0.0});
  double masse_volumique(0.1);
  double hauteur(1.5);
  double rayon(0.5);

  QApplication a(argc, argv);
  GLWidget w(P,P_point,masse_volumique,hauteur,rayon,origine);
  w.show();
  return a.exec();
}
