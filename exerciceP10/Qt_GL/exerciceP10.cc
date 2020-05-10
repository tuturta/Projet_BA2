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
  Systeme systeme1;
  Systeme systeme2;
  Systeme systemeSimple_VS_General;

  ConeSimple cone1({0.523599,0.0,0.0}, //P
                   {0.0,0.0,60.0},     //P_point
                   0.1,                //Masse volumique
                   1.5,                //Hauteur
                   0.5,                //Rayon
                   {0.0,0.0,0.0});     //Origine

  ConeSimple cone2({0.785398, 0.0,0.0}, //P
                   {0,0.0,40.0},        //P_point
                   0.1,                 //Masse Volumique
                   1.5,                 //Hauteur
                   0.5,                 //Rayon
                   {1.0,0.0,0.0});      //Origine
  ConeSimple cone3({0.1, 0.0,0.0}, //P
                   {0,0.0,120.0},        //P_point
                   0.3,                 //Masse Volumique
                   1.5,                 //Hauteur
                   1.5,                 //Rayon
                   {2.0,0.0,0.0});      //Origine
  ConeGeneral coneG({0.523599,0.0,0.0}, //P
                    {0.0,0.0,60.0},     //P_point
                    0.1,                //Masse volumique
                    1.5,                //Hauteur
                    0.5,                //Rayon
                    {0.0,0.0,0.0});     //Origine

  systeme1.ajoute_toupie(cone1);
  systeme1.ajoute_toupie(cone2);

  systeme2.ajoute_toupie(cone1);
  systeme2.ajoute_toupie(cone2);
  systeme2.ajoute_toupie(cone3);

  systemeSimple_VS_General.ajoute_toupie(cone1);
  systemeSimple_VS_General.ajoute_toupie(coneG);

  QApplication a(argc, argv);
  GLWidget<Systeme> w(systemeSimple_VS_General); //A adapter pour un systeme

  w.show();
  return a.exec();
  //return 0;
}
