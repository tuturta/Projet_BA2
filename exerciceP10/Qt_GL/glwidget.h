#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>        // Classe pour faire une fenêtre OpenGL
#include <QTime>                // Classe pour gérer le temps

// ESSAI LEA
#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>
#include <iostream>


//#include <memory> //arthur

#include "vue_opengl.h"
//#include "../general/Classe_Integrable/Classe_Toupie/Toupie.h"
//#include "../general/Classe_Systeme/Systeme.h"
#include "../general/Classe_Integrateur/Integrateur.h"
#include "../general/Classe_Vecteur/Vecteur.h"

template<typename Type>
class GLWidget : public QOpenGLWidget
{
public:
  GLWidget(Type const& a_dessiner, QWidget* parent = nullptr)
    : QOpenGLWidget(parent), contenu(a_dessiner)
    {contenu.setSupport(&vue); }
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
  Type contenu;

  // Integrateur pour faire évoluer la toupie :
  IntegrateurEulerCromer integrateur;

  // position de la souris
    QPoint lastMousePosition;
};


// ======================================================================
template<typename Type>
void GLWidget<Type>::initializeGL()
{
  vue.init();
  timerId = startTimer(20);
}

// ======================================================================
template<typename Type>
void GLWidget<Type>::resizeGL(int width, int height)
{
  /* On commance par dire sur quelle partie de la
   * fenêtre OpenGL doit dessiner.
   * Ici on lui demande de dessiner sur toute la fenêtre.
   */
  glViewport(0, 0, width, height);

  /* Puis on modifie la matrice de projection du shader.
   * Pour ce faire on crée une matrice identité (constructeur
   * par défaut), on la multiplie par la droite par une matrice
   * de perspective.
   * Plus de détail sur cette matrice
   *     http://www.songho.ca/opengl/gl_projectionmatrix.html
   * Puis on upload la matrice sur le shader à l'aide de la
   * méthode de la classe VueOpenGL
   */
  QMatrix4x4 matrice;
  matrice.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
  vue.setProjection(matrice);
}

// ======================================================================
template<typename Type>
void GLWidget<Type>::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  contenu.dessine();
}


// ======================================================================
template<typename Type>
void GLWidget<Type>::keyPressEvent(QKeyEvent* event)
{
  constexpr double petit_angle(5.0); // en degrés
  constexpr double petit_pas(1.0);

  switch (event->key()) {

  case Qt::Key_Left:
    vue.rotate(petit_angle, 0.0, -1.0, 0.0);
    break;

  case Qt::Key_Right:
    vue.rotate(petit_angle, 0.0, +1.0, 0.0);
    break;

  case Qt::Key_Up:
    vue.rotate(petit_angle, -1.0, 0.0, 0.0);
    break;

  case Qt::Key_Down:
    vue.rotate(petit_angle, +1.0, 0.0, 0.0);
    break;

  case Qt::Key_PageUp:
  case Qt::Key_W:
    vue.translate(0.0, 0.0,  petit_pas);
    break;

  case Qt::Key_PageDown:
  case Qt::Key_S:
    vue.translate(0.0, 0.0, -petit_pas);
    break;

  case Qt::Key_A:
    vue.translate( petit_pas, 0.0, 0.0);
    break;

  case Qt::Key_D:
    vue.translate(-petit_pas, 0.0, 0.0);
    break;

  case Qt::Key_R:
    vue.translate(0.0, -petit_pas, 0.0);
    break;

  case Qt::Key_F:
    vue.translate(0.0,  petit_pas, 0.0);
    break;

  case Qt::Key_Q:
    vue.rotate(petit_angle, 0.0, 0.0, -1.0);
    break;

  case Qt::Key_E:
    vue.rotate(petit_angle, 0.0, 0.0, +1.0);
    break;

  case Qt::Key_Home:
    vue.initializePosition();
    break;

  case Qt::Key_Space:
    pause();
    break;
  };

  update(); // redessine
}

// ======================================================================


double t(0);
template<typename Type>
void GLWidget<Type>::timerEvent(QTimerEvent* event)
{
  Q_UNUSED(event);

  double dt = /*chronometre.restart()/1000;*/ 0.001;
  integrateur.evolue(contenu,dt);
  t+=dt;
  //std::cout << t << " " /*<< contenu.getP() */<< std::endl;
  update();
}

// ======================================================================
template<typename Type>
void GLWidget<Type>::pause()
{
  if (timerId == 0) {
    // dans ce cas le timer ne tourne pas alors on le lance
    timerId = startTimer(20);
    chronometre.restart();
  } else {
    // le timer tourne alors on l'arrête
    killTimer(timerId);
    timerId = 0;
  }
}

template<typename Type>
void GLWidget<Type>::mousePressEvent(QMouseEvent* event)
{
  lastMousePosition = event->pos();
}

template<typename Type>
void GLWidget<Type>::mouseMoveEvent(QMouseEvent* event)
{
  /* If mouse tracking is disabled (the default), the widget only receives
   * mouse move events when at least one mouse button is pressed while the
   * mouse is being moved.
   *
   * Pour activer le "mouse tracking" if faut lancer setMouseTracking(true)
   * par exemple dans le constructeur de cette classe.
   */

  if (event->buttons() & Qt::LeftButton) {
    constexpr double petit_angle(.4); // en degrés

    // Récupère le mouvement relatif par rapport à la dernière position de la souris
    QPointF d = event->pos() - lastMousePosition;
    lastMousePosition = event->pos();

    vue.rotate(petit_angle * d.manhattanLength(), d.y(), d.x(), 0);

    update();
  }
}


#endif // GLWIDGET_H
