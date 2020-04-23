#ifndef VUEOPENGL_H
#define VUEOPENGL_H

#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include "../general/support_a_dessin.h"
#include "../general/Classe_Integrable/Classe_Toupie/Toupie.h"

class VueOpenGL : public SupportADessin {
 public:
  // méthode(s) de dessin (héritée(s) de SupportADessin)
  virtual void dessine(ConeSimple const& objet) override;
  virtual void dessine(Objet_en_chute_libre const& objet) override;
  virtual void dessine(Toupie const& objet) override;
  virtual void dessine(Systeme const& objet) override;

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
  void dessineToupie(QMatrix4x4 const& point_de_vue = QMatrix4x4() );
  void dessinePyramide(QMatrix4x4 const& point_de_vue = QMatrix4x4() );
  void dessineRepere(QMatrix4x4 const& point_de_vue = QMatrix4x4() );
  void dessineSol(QMatrix4x4 const& point_de_vue = QMatrix4x4() );
  QMatrix4x4 matrice_dessin(Integrable const& a_dessiner) const;


 private:
  // Un shader OpenGL encapsulé dans une classe Qt
  QOpenGLShaderProgram prog;

  // Caméra
  QMatrix4x4 matrice_vue;
};

#endif
