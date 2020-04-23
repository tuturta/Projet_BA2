#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs
#include "../general/Classe_Integrable/Classe_Toupie/Toupie.h"
#include <cmath>
// ======================================================================
void VueOpenGL::dessine(ConeSimple const& a_dessiner)
{
    dessineRepere();
    //dessineSol();
  /*// Dessine le 1er cube (à l'origine)
    dessineCube();

  
  // Dessine le 2e cube
   matrice.translate(0.0, 1.5, 0.0);
   matrice.scale(0.25);2
  dessineCube(matrice);

  // Dessine le 3e cube
  matrice.setToIdentity();
  matrice.translate(0.0, 0.0, 1.5);
  matrice.scale(0.25);
  matrice.rotate(45.0, 0.0, 1.0, 0.0);
  dessineCube(matrice);*/
  
  QMatrix4x4 matrice;
  matrice.setToIdentity();
  
  double psi(a_dessiner.getP().coeff(1)*180/M_PI);  ///angles en degrés
  double theta(a_dessiner.getP().coeff(0)*180/M_PI);
  double phi(a_dessiner.getP().coeff(2)*180/M_PI);
  std::cout << "psi: " << psi << "; theta : " << theta << "; phi: " << std::endl;
  matrice.rotate(phi,0.0, 0.0, 1.0/*sin(theta)*sin(psi), -sin(theta)*cos(psi), cos(theta)?*/); //rotation propre PHI autour de Oz'
  matrice.rotate(theta ,1.0, 0.0, 0.0 /*cos(psi) , sin(psi) , 0 ?*/); //nutation THETA autour de l'axe nodal
  matrice.rotate(psi,0.0 , 0.0 , 1.0); // précession PSI autour de Oz

  matrice.scale(0.5);
  cone.initialize(a_dessiner.getHauteur(),a_dessiner.getRayon());
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // passe en mode "fil de fer"
  dessineConeSimple(matrice,1.0,0.5,1.0); // rouge
}

// ======================================================================

void VueOpenGL::dessine(Toupie const& a_dessiner)
{
  QMatrix4x4 matrice;
  matrice.setToIdentity();
    
  double psi(a_dessiner.getP().coeff(1)*180/M_PI);  ///angles en degrés
  double theta(a_dessiner.getP().coeff(0)*180/M_PI); 
  double phi(a_dessiner.getP().coeff(2)*180/M_PI);

  matrice.rotate(psi,0 , 0 , 1); // précession PSI autour de Oz
  matrice.rotate(theta , cos(psi) , sin(psi) , 0); //nutation THETA autour de l'axe nodal
  matrice.rotate(phi,sin(theta)*sin(psi), -sin(theta)*cos(psi), cos(theta)); //rotation propre PHI autour de Oz'
  matrice.scale(0.5);
  dessineToupie(matrice);
}
// ======================================================================
void VueOpenGL::dessine(Objet_en_chute_libre const& a_dessiner)
{
    dessineRepere();
  /*// Dessine le 1er cube (à l'origine)
    dessineCube();

  // Dessine le 2e cube
   matrice.translate(0.0, 1.5, 0.0);
   matrice.scale(0.25);2
  dessineCube(matrice);

  // Dessine le 3e cube
  matrice.setToIdentity();
  matrice.translate(0.0, 0.0, 1.5);
  matrice.scale(0.25);
  matrice.rotate(45.0, 0.0, 1.0, 0.0);
  dessineCube(matrice);*/

  QMatrix4x4 matrice;
  // Dessine le 4e cube
  matrice.setToIdentity();
    
  double psi(a_dessiner.getP().coeff(1)*180.0/M_PI);  ///angles en degrés
  double theta(a_dessiner.getP().coeff(0)*180.0/M_PI);
  double phi(a_dessiner.getP().coeff(2)*180.0/M_PI);

  matrice.rotate(phi,0.0, 0.0, 1.0); //rotation propre PHI autour de Oz'
  matrice.rotate(theta, 1.0 , 0.0 , 0.0); //nutation THETA autour de l'axe nodal
  matrice.rotate(psi,0.0 , 0.0 , 1.0); // précession PSI autour de Oz

  matrice.scale(0.5);
  dessineToupie(matrice);
}
// ======================================================================
    //EMPLACEMENT POUR DESSINE(SYSTEME)
// ======================================================================
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
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  cone.initialize(); // initialise le cone
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
  /*matrice_vue.rotate(90.0, 0.0, 1.0, 0.0);
  matrice_vue.rotate(45.0, 0.0, 0.0, 1.0);*/
}

// ======================================================================
void VueOpenGL::translate(double x, double y, double z)
{
  /* Multiplie la matrice de vue par LA GAUCHE.
   * Cela fait en sorte que la dernière modification apportée
   * à la matrice soit appliquée en dernier (composition de fonctions).
   */
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

// ======================================================================
void VueOpenGL::dessineToupie (QMatrix4x4 const& point_de_vue)
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

/********* MÉTHODE SIMPLE POUR DESSINER UN CONE, MAIS PEU EFFICACE ******************************************************
 * pour information, elle ne peut plus être utilisée dans cette version du code *
void VueOpenGL::dessineConeSimple( double hauteur, double rayon, const QMatrix4x4 &point_de_vue) //Cone de hauteur h,rayon r
{
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    /* Notre méthode : on dessine un cône comme un empilement de cercles concentriques
     * dont les rayons diminuent quand la position verticale diminue*//*


    glBegin(GL_LINES);
    double pas_hauteur(0.1); //À voir : plus de précision et sans ralentissement  ??
    double pas_angle(0.1);
    double pas_couleur(0.0028);
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
***********************************************************************************************************************/

void VueOpenGL::dessineConeSimple (QMatrix4x4 const& point_de_vue,
                               double rouge, double vert, double bleu)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  prog.setAttributeValue(CouleurId, rouge, vert, bleu);  // met la couleur
  cone.draw(prog, SommetId);                           // dessine la sphère
}


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

void VueOpenGL::dessineSol (QMatrix4x4 const& point_de_vue)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_QUADS);

   prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0); //Blanc
   prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
   prog.setAttributeValue(SommetId, 10.0, 0.0, 0.0);
   prog.setAttributeValue(SommetId, 10.0, 10.0, 0.0);
   prog.setAttributeValue(SommetId, 0.0, 10.0, 0.0);

  glEnd();


}
