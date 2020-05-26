#ifndef GLSPHERE_TRONQUEE_H
#define GLSPHERE_TRONQUEE_H

#include <QGLBuffer>
#include <QOpenGLShaderProgram>

class GLSphere_Tronquee
{
public:
 GLSphere_Tronquee()
   : vbo(QGLBuffer::VertexBuffer), ibo(QGLBuffer::IndexBuffer)
 {}

  void initialize(double hauteur, double rayon, GLuint slices = 25, GLuint stacks = 25);

  void draw(QOpenGLShaderProgram& program, int attributeLocation);

  void bind();
  void release();

private:
  QGLBuffer vbo, ibo;
  GLuint vbo_sz;
  GLuint ibo_sz[3];
};

#endif // GLSPHERE_TRONQUEE_H
