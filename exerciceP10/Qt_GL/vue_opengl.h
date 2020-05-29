#ifndef VUEOPENGL_H
#define VUEOPENGL_H

#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include <array>
#include "../general/support_a_dessin.h"
#include "../general/Classe_Integrable/Classe_Toupie/Toupie.h"
#include "glcone.h"
#include "glsphere_tronquee.h"


class VueOpenGL : public SupportADessin {
 public:


  // méthode(s) de dessin (héritée(s) de SupportADessin)
    virtual void dessine(ConeGeneral const& objet) override;
    virtual void dessine(Objet_en_chute_libre const& objet) override;
    virtual void dessine(Toupie const& objet) override;
    virtual void dessine(ToupieChinoiseGenerale const& objet) override;


  // méthodes de (ré-)initialisation
  void init();
  void initializePosition();

  // méthode set
  void setProjection(QMatrix4x4 const& projection)
  { prog.setUniformValue("projection", projection); }

  // Méthodes set
  void translate(double x, double y, double z);
  void rotate(double angle, double dir_x, double dir_y, double dir_z);

  // méthode utilitaire offerte pour simplifier
  void dessineCube(QMatrix4x4 const& point_de_vue = QMatrix4x4());
  void dessineConeSimple(QMatrix4x4 const& point_de_vue, Couleur couleur);
  void dessinePyramide(QMatrix4x4 const& point_de_vue = QMatrix4x4() );
  void dessineToupieChinoise (QMatrix4x4 const& point_de_vue, Couleur couleur) ;
  void dessineRepere(QMatrix4x4 const& point_de_vue = QMatrix4x4() );
  void dessineSol(QMatrix4x4 const& point_de_vue = QMatrix4x4() );
  void matrice_inertie(QMatrix4x4& matrice, Toupie const& a_dessiner) const;
  void dessineTrace( std::vector<Vecteur> const& positions);
  void dessineCM( Toupie const& a_dessiner, QMatrix4x4 const& point_de_vue = QMatrix4x4());

  RVBColor ColorTranslate(Couleur couleur) const;                                           //Convertit une couleur de type "Couleur" en couleur de type RVB lisible par le shader

//test
  void dessineConeSimplebug(double h, double r, QMatrix4x4 const& mat);



 private:
  // Un shader OpenGL encapsulé dans une classe Qt
  QOpenGLShaderProgram prog;
  //Un cone
  GLCone cone;
  //Un sphère tronquée
  GLSphere_Tronquee sphere_tronquee;
  // Caméra
  QMatrix4x4 matrice_vue;
};

#endif
