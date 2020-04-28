#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>        // Classe pour faire une fenêtre OpenGL
#include <QTime>                // Classe pour gérer le temps

//#include <memory> ***ESSAI ARTHUR***********************

#include "vue_opengl.h"
#include "../general/Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../general/Classe_Integrateur/Integrateur.h"
#include "../general/Classe_Vecteur/Vecteur.h"


class GLWidget : public QOpenGLWidget
/* La fenêtre hérite de QOpenGLWidget ;
 * les événements (clavier, souris, temps) sont des méthodes virtuelles à redéfinir.
 */
{
public:
  GLWidget(ConeSimple const& a_dessiner, QWidget* parent = nullptr) //ON DOIT TROUVER COMMENT FAIRE DE FACON UNIVERSELLE
    : QOpenGLWidget(parent)
    , contenu(a_dessiner)
  {contenu.setSupport(&vue);}
  virtual ~GLWidget() {}
private:
  // Les 3 méthodes clés de la classe QOpenGLWidget à réimplémenter
  virtual void initializeGL()                  override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL()                       override;

  // Méthodes de gestion d'évènements
  virtual void keyPressEvent(QKeyEvent* event) override;
  virtual void timerEvent(QTimerEvent* event)  override;
  virtual void mousePressEvent(QMouseEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent* event)  override;

  // Méthodes de gestion interne
  void pause();

  // Vue : ce qu'il faut donner au contenu pour qu'il puisse se dessiner sur la vue
  VueOpenGL vue;

  // Timer
  int timerId;
  // pour faire évoluer les objets avec le bon "dt"
  QTime chronometre;

  // objets à dessiner, faire évoluer
  ConeSimple contenu;

  // Integrateur pour faire évoluer la toupie :
  IntegrateurEulerCromer integrateur;

  // position de la souris
    QPoint lastMousePosition;
};

#endif // GLWIDGET_H
