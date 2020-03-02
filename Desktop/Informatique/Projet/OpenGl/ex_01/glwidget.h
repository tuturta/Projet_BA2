#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>        // Classe pour faire une fenêtre OpenGL
#include <QOpenGLShaderProgram> // Classe qui wrap les fonctions OpenGL liées aux shaders

class GLWidget : public QOpenGLWidget
/* La fenêtre hérite de QOpenGLWidget ;
 * les événements (clavier, souris, temps) sont des méthodes virtuelles à redéfinir.
 */
{
public:
  GLWidget(QWidget* parent = nullptr)
    : QOpenGLWidget(parent) {}
  virtual ~GLWidget() {}

private:
  // Les 3 méthodes clés de la classe QOpenGLWidget à réimplémenter
  virtual void initializeGL()                  override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL()                       override;

  // Un shader OpenGL encapsulé dans une classe Qt
  QOpenGLShaderProgram prog;
};

#endif // GLWIDGET_H
