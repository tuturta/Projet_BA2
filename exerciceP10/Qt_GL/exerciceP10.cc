#include <QApplication>
#include <iostream>
#include "glwidget.h"
#include "../general/Classe_Vecteur/Vecteur.h"
#include "../general/Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../general/support_a_dessin.h"
#include <iostream>
using  namespace std;

int main(int argc, char* argv[])
{
  Vecteur P({0.0,0.0,0.0});
  Vecteur P_point({0.523599,0.0,60.0});
  Vecteur origine({0.0,0.0,0.0});
  Vecteur origine2({5.0,0.0,0.0});
  double masse_volumique(0.1);
  double hauteur(1.5);
  double rayon(0.5);
  ConeSimple cone1(P,P_point,masse_volumique,hauteur,rayon,origine);
  ConeSimple cone2(P,P_point,masse_volumique,hauteur,rayon,origine2);
  TextViewer support(cout);
  Systeme systeme1(&support);


  systeme1.ajoute_toupie(cone1);
  systeme1.ajoute_toupie(cone2);
  QApplication a(argc, argv);
  GLWidget<Systeme> w(systeme1); //A adapter pour un systeme

  w.show();
  return a.exec();
  //return 0;
}
