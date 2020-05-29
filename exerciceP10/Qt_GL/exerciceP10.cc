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

  IntegrateurEulerCromer integrateur_e;
  IntegrateurNewmark integrateur_n;
  IntegrateurRungeKutta integrateur_rk;


  ConeSimple cone1({0.0,0.523599,0.0},      //P (psi-theta-phi)
                   {0.0,0.0,60.0},    //P_point
                   0.1,                //Masse volumique
                   1.5,                //Hauteur
                   0.5,                //Rayon
                   {3.0,3.0,0.0},       //Origine
                   vert);

  ConeGeneral cone1G({0.0, 0.523599,0.0}, //P (psi-theta-phi)
                   {0.0,0.0,60.0},          //P_point
                   0.1,                   //Masse Volumique
                   1.5,                   //Hauteur
                   0.5,                   //Rayon
                   {0.0,0.0,0.0},
                   bleu);        //Origine dans le ref absolu

  //Toupie avec trace en fleur

  ConeSimple coneTrace({0.0,0.4,0.0},      //P (psi-theta-phi)
                       {0.0,0.0,70.0},    //P_point
                       0.1,                //Masse volumique
                       1.0,                //Hauteur
                       0.45,                //Rayon
                       {0.0,0.0,0.0},       //Origine
                       jaune);

//Toupies roulantes qui tournent

  ToupieChinoise flipflop({0.0,0.11,0.0},
                  {50.0,0.0,0.0},
                  0.1,
                  0.08,
                  0.6,
                  {5.0,0.0,0.0},
                  vert         );

  ToupieChinoiseGenerale flipflopG({0.0,0.11,0.0},
                          {50.0,0.0,0.0},
                          0.1,
                          0.08,
                          0.6,
                          {0.0,5.0,0.0},
                          bleu);


  //Balanciers:

  ToupieChinoise balancier( {0.0,0.75,0.0},
                            {0.0,0.0,0.0},
                            0.1,
                            0.08,
                            0.6,
                            {3.0,0.0,0.0},
                            vert);

  ToupieChinoiseGenerale balancierG ( {0.0,0.75,0.0},
                            {0.0,0.0,0.0},
                            0.1,
                            0.08,
                            0.6,
                            {0.0,3.0,0.0},
                            bleu);



  Systeme systeme1(&integrateur_rk);


  systeme1.ajoute_toupie(cone1);
  systeme1.ajoute_toupie(cone1G);
  //systeme1.ajoute_toupie(coneTrace);
  //systeme1.ajoute_toupie(balancier);
  //systeme1.ajoute_toupie(balancierG);
  //systeme1.ajoute_toupie(flipflop);
 // systeme1.ajoute_toupie(flipflopG);


  QApplication a(argc, argv);
  GLWidget w(systeme1);

  w.show();
  return a.exec();
  //return 0;
}
