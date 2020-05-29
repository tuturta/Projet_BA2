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

  VueOpenGL vue;
  IntegrateurEulerCromer integrateur_e;
  IntegrateurNewmark integrateur_n;
  IntegrateurRungeKutta integrateur_rk;

  ConeSimple cone1({0.0,0.523599,0.0},      //P (psi-theta-phi)
                   {0.0,0.0,60.0},    //P_point
                   0.1,                //Masse volumique
                   1.5,                //Hauteur
                   0.5,                //Rayon
                   {0.0,0.0,0.0},      //Origine
                   &vue);

  ConeSimple cone2({0.0, 0.785398,0.0}, //P (psi-theta-phi)
                   {0,0.0,40.0},          //P_point
                   0.1,                   //Masse Volumique
                   1.5,                   //Hauteur
                   0.5,                   //Rayon
                   {0.0,1.0,0.0});        //Origine dans le ref absolu

  ConeSimple coneTrace({0.0,0.4,0.0},      //P (psi-theta-phi)
                       {0.0,0.0,70.0},    //P_point
                       0.1,                //Masse volumique
                       2.0,                //Hauteur
                       0.9,                //Rayon
                       {1.0,0.0,0.0});     //Origine


  ToupieChinoise flipflop({0.0,0.11,0.0},
                  {50.0,0.0,0.0},
                  0.1,
                  0.02,
                  0.15,
                  {0.0,0.0,0.0});

  ToupieChinoise balancier( {0.0,0.75,0.0},
                            {0.0,0.0,0.0},
                            0.1,
                            0.02,
                            0.15,
                            {0.0,0.0,0.0});

  ToupieChinoiseGenerale roulante({0.0,0.11,0.0},
                          {50.0,0.0,0.0},
                          0.1,
                          0.02,
                          0.15,
                          {0.0,0.0,0.0});

  Systeme systeme1(&integrateur_e);


  systeme1.ajoute_toupie(cone1);
  //systeme1.ajoute_toupie(cone2);
  //systeme1.ajoute_toupie(cone1);
  QApplication a(argc, argv);
  GLWidget w(systeme1);

  w.show();
  return a.exec();
  //return 0;
}
