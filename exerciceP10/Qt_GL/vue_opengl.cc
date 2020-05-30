#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs
#include "../general/Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../general/Classe_Integrable/Integrable.h"
#include "../general/Classe_Systeme/Systeme.h"
#include "../general/Classe_Vecteur/Vecteur.h"
#include <cmath>
#include <iostream>
#include <vector>

// ======================================================================MATRICE DESSIN
void VueOpenGL::matrice_inertie(QMatrix4x4& matrice, Toupie const& a_dessiner) const{
  double psi(a_dessiner.getP().coeff(0)*180.0/M_PI);  ///angles en degrés
  double theta(a_dessiner.getP().coeff(1)*180.0/M_PI);
  double phi(a_dessiner.getP().coeff(2)*180.0/M_PI);

  matrice.rotate(psi,0.0 , 0.0 , 1.0 ); // précession PSI autour de Oz
  matrice.rotate(theta ,1.0, 0.0, 0.0 ); // nutation THETA autour de l'axe nodal
  matrice.rotate(phi,0.0,0.0,1.0 ); //rotation propre PHI autour de Oz'

}


// ======================================================================DESSINE(TOUPIE)

void VueOpenGL::dessine(Toupie const& a_dessiner)
{
    std::cout << "COUCOU JE SUIS UNE TOUPIE" << std::endl;
    dessineRepere();

}

// ======================================================================DESSINE(CONE)
void VueOpenGL::dessine(ConeGeneral const& a_dessiner)
{

   //On initialise la matrice de dessin
   QMatrix4x4 matrice;
   matrice.setToIdentity();

   //Coordonnées du point de contact
   double xA(a_dessiner.getPoint_de_conact().coeff(0));
   double yA(a_dessiner.getPoint_de_conact().coeff(1));
   double zA(a_dessiner.getPoint_de_conact().coeff(2));


  //On se place au niveau du point de contact, c'est de là que se dessine le cône:
  matrice.translate(xA,yA,zA);


  //On se place dans repère d'inertie:
  matrice_inertie(matrice, a_dessiner);


  //En fonction des options choisies, on active/désactive le repère d'inertie, la trace et le sol
  dessineAccessoires(matrice,a_dessiner);                                            //On dessine le repère d'inertie
  dessineCM(a_dessiner);

  //On dessine le cone:
  cone.initialize(a_dessiner.getHauteur(),a_dessiner.getRayon());   //établit le modèle du cône à dessiner.
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);                        // passe en mode "fil de fer"
  dessineConeSimple(matrice,a_dessiner.getColor());
}

// ======================DESSINE(TOUPIE_CHINOISE)=============================
void VueOpenGL::dessine(ToupieChinoiseGenerale const& a_dessiner)
{
  std::cout << "vecteur OC: " << a_dessiner.vecteurOC() << std::endl;
  //On place le repère du dessin au centre de la sphère(point à partir duquel s'effectue le dessin)
  QMatrix4x4 matrice;
  matrice.setToIdentity();
  double Cx(a_dessiner.vecteurOC().coeff(0));
  double Cy(a_dessiner.vecteurOC().coeff(1));
  double Cz(a_dessiner.vecteurOC().coeff(2));
  matrice.translate(Cx,Cy,Cz);

  //On se place dans repère d'inertie
  matrice_inertie(matrice, a_dessiner);

  //En fonction des options choisies, on active/désactive le repère d'inertie, le repère galiléen, la trace et le sol
  dessineAccessoires(matrice,a_dessiner);
  dessineCM(a_dessiner);

  //On dessine la sphère tronquée dans le repère du dessin
  sphere_tronquee.initialize(a_dessiner.getHauteur(),a_dessiner.getRayon()); //établit le modèle du cône à dessiner.
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);                                 // passe en mode "fil de fer"
  dessineToupieChinoise(matrice,a_dessiner.getColor());
}


// ======================DESSINE(OBJET EN ...)=============================
void VueOpenGL::dessine(Objet_en_chute_libre const& a_dessiner)
{
  QMatrix4x4 matrice;
  matrice.setToIdentity();
    
  double psi(a_dessiner.getP().coeff(1)*180.0/M_PI);  ///angles en degrés
  double theta(a_dessiner.getP().coeff(1)*180.0/M_PI);
  double phi(a_dessiner.getP().coeff(2)*180.0/M_PI);

  matrice.rotate(phi,0.0, 0.0, 1.0);      //rotation propre PHI autour de Oz'
  matrice.rotate(theta, 1.0 , 0.0 , 0.0); //nutation THETA autour de l'axe nodal
  matrice.rotate(psi,0.0 , 0.0 , 1.0);    // précession PSI autour de Oz

  matrice.scale(0.5);
  dessineCube(matrice);
}

// ============================DESSINETRACE=================================

void VueOpenGL::dessineTrace(std::vector<Vecteur> const& positions)
{

    prog.setUniformValue("vue_modele", matrice_vue*QMatrix4x4());
    glBegin(GL_POINTS);
    prog.setAttributeValue(CouleurId,1.0,0.0,0.0); //rouge
    for(auto point: positions) {
        prog.setAttributeValue(SommetId,point.coeff(0),point.coeff(1), point.coeff(2));

    }

    glEnd();

}

// ============================INITIALISATION=================================
void VueOpenGL::init()
{
  /* Initialise notre vue OpenGL.
   * Dans cet exemple, nous créons et activons notre shader.
   *
   * En raison du contenu des fichiers *.glsl, le shader de cet exemple
   * NE permet QUE de dessiner des primitives colorées
   * (pas de textures, brouillard, reflets de la lumière ou autres).
   *
   * Il est séparé en deux parties VERTEX et FRAGMENT.
   * Le VERTEX :
   * - récupère pour chaque sommet des primitives de couleur (dans
   *     l'attribut couleur) et de position (dans l'attribut sommet)
   * - multiplie l'attribut sommet par les matrices 'vue_modele' et
   *     'projection' et donne le résultat à OpenGL
   *   - passe la couleur au shader FRAGMENT.
   *
   * Le FRAGMENT :
   *   - applique la couleur qu'on lui donne
   */

  prog.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/vertex_shader.glsl");
  prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

  /* Identifie les deux attributs du shader de cet exemple
   * (voir vertex_shader.glsl).
   *
   * L'attribut identifié par 0 est particulier, il permet d'envoyer un
   * nouveau "point" à OpenGL
   *
   * C'est pourquoi il devra obligatoirement être spécifié et en dernier
   * (après la couleur dans cet exemple, voir plus bas).
   */

  prog.bindAttributeLocation("sommet",  SommetId);
  prog.bindAttributeLocation("couleur", CouleurId);

  // Compilation du shader OpenGL
  prog.link();

  // Activation du shader
  prog.bind();

  /* Activation du "Test de profondeur" et du "Back-face culling"
   * Le Test de profondeur permet de dessiner un objet à l'arrière-plan
   * partielement caché par d'autres objets.
   *
   * Le Back-face culling consiste à ne dessiner que les face avec ordre
   * de déclaration dans le sens trigonométrique.
   */
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
  glClearDepth(1.0f);                   // Set background depth to farthest
  dessineSol();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  initializePosition();

}

// ======================================================================
void VueOpenGL::initializePosition()
{
  // position initiale
  matrice_vue.setToIdentity();
  matrice_vue.translate(0.0, 0.0, -4.0);
  matrice_vue.rotate(30.0,1.0,0.0,0.0);
  matrice_vue.rotate(30.0,0.0,1.0,0.0);
  matrice_vue.rotate(270.0,1.0,0.0,0.0); //met l'axe z en haut
}

// ======================================================================
void VueOpenGL::translate(double x, double y, double z)
{
  /* Multiplie la matrice de vue par LA GAUCHE.
   * Cela fait en sorte que la dernière modification apportée
   * à la matrice soit appliquée en dernier (composition de fonctions).*/


  QMatrix4x4 translation_supplementaire;
  translation_supplementaire.translate(x, y, z);
  matrice_vue = translation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z)
{
  // Multiplie la matrice de vue par LA GAUCHE
  QMatrix4x4 rotation_supplementaire;
  rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
  matrice_vue = rotation_supplementaire * matrice_vue;
}

// =====================================================================dessineCube ? ->CUBE -> A ENLEVER ?
void VueOpenGL::dessineCube (QMatrix4x4 const& point_de_vue)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_QUADS);
  // face coté X = +1
  prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

  // face coté X = -1
  prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

  // face coté Y = +1
  prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

  // face coté Y = -1
  prog.setAttributeValue(CouleurId, 0.0, 1.0, 1.0); // cyan
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);

  // face coté Z = +1
  prog.setAttributeValue(CouleurId, 1.0, 1.0, 0.0); // jaune
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

  // face coté Z = -1
  prog.setAttributeValue(CouleurId, 1.0, 0.0, 1.0); // magenta
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

  glEnd();
}

//========================================================================DESSINECONE

/********* MÉTHODE SIMPLE POUR DESSINER UN CONE, MAIS PEU EFFICACE ******************
 * pour information, elle ne peut plus être utilisée dans cette version du code ******/

void VueOpenGL::dessineConeSimplebug( double hauteur, double rayon, const QMatrix4x4 &point_de_vue)
{
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

    //on dessine un cône comme un empilement de cercles concentriques
    //dont les rayons diminuent quand la position verticale diminue


    glBegin(GL_LINES);
    double pas_hauteur(0.1); //À voir : plus de précision et sans ralentissement  ??
    double pas_angle(0.1);
    for(double z(hauteur); z>=0.0 ; z-=pas_hauteur) {
        for(double angle(0.0); angle<360.0; angle+=pas_angle) {
            prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);
            double rayon_actuel(rayon*z/hauteur);
            prog.setAttributeValue(SommetId, cos(angle)*rayon_actuel, sin(angle)*rayon_actuel, z);
        }
    }
    //traits verticaux
    //
    glEnd();


}


//===========================================================================DESSINEPYRAMIDE

void VueOpenGL::dessinePyramide (QMatrix4x4 const& point_de_vue) //PYRAMIDE DE HAUTEUR 1.5 et de BASE 0.5 (de rayon)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  glBegin(GL_QUADS);

  prog.setAttributeValue(CouleurId, 0.0, 1.0, 1.0); // cyan // Base carrée
  prog.setAttributeValue(SommetId, +0.5, +0.5, +1.5);
  prog.setAttributeValue(SommetId, +0.5, -0.5, +1.5);
  prog.setAttributeValue(SommetId, -0.5, -0.5, +1.5);
  prog.setAttributeValue(SommetId, -0.5, +0.5, +1.5);

  glEnd();

  glBegin(GL_TRIANGLES);


  // coté droit
  prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, +0.5, +0.5, 1.5);
  prog.setAttributeValue(SommetId, +0.5, -0.5, 1.5);

  // coté gauche
  prog.setAttributeValue(CouleurId, 1.0, 1.0, 0.0); // jaune
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, -0.5, +0.5, 1.5);
  prog.setAttributeValue(SommetId, -0.5, -0.5, 1.5);

  // face
  prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, +0.5, +0.5, 1.5);
  prog.setAttributeValue(SommetId, -0.5, +0.5, 1.5);

  // derriere
  prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, -0.5, -0.5, 1.5);
  prog.setAttributeValue(SommetId, +0.5, -0.5, 1.5);

  glEnd();

}

//==========================================================================DESSINEREPERE

void VueOpenGL::dessineRepere (QMatrix4x4 const& point_de_vue)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_LINES);

   prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); //Rouge
   prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0); ///Axe x
   prog.setAttributeValue(SommetId, 5.0, 0.0, 0.0);

   prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); //Vert
   prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0); ///Axe y
   prog.setAttributeValue(SommetId, 0.0, 5.0, 0.0);

   prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); //Bleu
   prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0); ///Axe z
   prog.setAttributeValue(SommetId, 0.0, 0.0, 5.0);

  glEnd();


}

//========================================================================DESSINESOL

void VueOpenGL::dessineSol (QMatrix4x4 const& point_de_vue)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_QUADS);
    double x0 (5.0);
    double y0(5.0);
    double z0(0.0);
    double dx(5.0);
    double dy(5.0);

   prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0); //Blanc
   prog.setAttributeValue(SommetId, x0-dx,y0-dy, z0);
   prog.setAttributeValue(SommetId, x0+dx, y0-dy, z0);
   prog.setAttributeValue(SommetId, x0+dx, y0+dy, z0);
   prog.setAttributeValue(SommetId, x0-dx, y0+dy, z0);

  glEnd();


}

//========================================================================DESSINE_TOUPIE_CHINOISE
void VueOpenGL::dessineToupieChinoise (QMatrix4x4 const& point_de_vue, Couleur couleur)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  prog.setAttributeValue(CouleurId, ColorTranslate(couleur)[0], ColorTranslate(couleur)[1], ColorTranslate(couleur)[2]);  // met la couleur
  sphere_tronquee.draw(prog, SommetId); // dessine la sphere tronquee
}

void VueOpenGL::dessineConeSimple (QMatrix4x4 const& point_de_vue, Couleur couleur)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  prog.setAttributeValue(CouleurId, ColorTranslate(couleur)[0], ColorTranslate(couleur)[1], ColorTranslate(couleur)[2]);  // met la couleur
  cone.draw(prog, SommetId); // dessine le cone simple
}

RVBColor VueOpenGL::ColorTranslate(Couleur color) const{
    
    switch(color){
        case blanc  : return {1.0, 1.0, 1.0};
        case noir   : return {0.0, 0.0, 0.0};
        case rouge  : return {1.0, 0.0, 0.0};
        case jaune  : return {1.0, 1.0, 0.0};
        case bleu   : return {0.0, 0.0, 1.0};
        case vert   : return {0.0, 1.0, 0.0};
        case violet : return {0.5, 0.0, 0.5};
        case orange : return {0.9, 0.5, 0.0};

    }

    return {1.0, 1.0, 1.0};

}



void VueOpenGL::dessineCM(Toupie const& a_dessiner, QMatrix4x4 const& point_de_vue){
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

    glBegin(GL_LINES);
    std::cout << "vecteurOG() : " << a_dessiner.vecteurOG() << std::endl;
    double x(a_dessiner.vecteurOG().coeff(0));
    double y(a_dessiner.vecteurOG().coeff(1));
    double z(a_dessiner.vecteurOG().coeff(2));
    double delta(0.05);

    prog.setAttributeValue(CouleurId, 1.0, 0.0, 1.0); //Magenta
    prog.setAttributeValue(SommetId, x, y, z+delta);
    prog.setAttributeValue(SommetId, x, y, z-delta);

    prog.setAttributeValue(SommetId, x, y+delta, z);
    prog.setAttributeValue(SommetId, x, y-delta, z);
    glEnd();

}

void VueOpenGL::sol(bool option) {
    sol_ = option;
}
void VueOpenGL::trace(bool option) {
    trace_ = option;
}
void VueOpenGL::repere_inertie(bool option) {
    repere_inertie_ = option;
}
void VueOpenGL::repere_galileen(bool option) {
    repere_galileen_ = option;
}

void VueOpenGL::dessineAccessoires(QMatrix4x4 const& matrice_inertie, Toupie const& a_dessiner){
    if(repere_inertie_){dessineRepere(matrice_inertie);}
    if(trace_){dessineTrace(a_dessiner.getPositions_CM());}
    if(sol_){dessineSol();}
    if(repere_galileen_){dessineRepere();}

}
