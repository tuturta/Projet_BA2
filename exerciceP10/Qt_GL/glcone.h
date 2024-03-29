#ifndef GLCONE_H
#define GLCONE_H

#include <QGLBuffer>
#include <QOpenGLShaderProgram>

/*Pour les graphismes, nous avons réussi à faire de nous même un cône
 * grâce au peu de connaissances que nous avons sur qt. Cependant,
 * notre méthode nécessite le calcul du 'maillage' du cône à chaque
 * pas de temps, ce qui ralentit considérablement l'éxécution du programme.
 * Vous pouvez trouver notre façon de dessiner un cone en commentaire
 * dans vue_opengl.cc.
 * Mais pour améliorer le graphisme, nous nous inspirons maintenant
 * de l'exercice 6 du tutoriel Opengl. Nous avons suffisamment compris
 * le code pour l'adapter à nos cones, bien que nous ne maitrisions
 * pas tous les concepts utilisés.
*/

class GLCone
{
public:
 GLCone()
   : vbo(QGLBuffer::VertexBuffer), ibo(QGLBuffer::IndexBuffer)
 {}

  void initialize(double h = 1.5 , double r = 0.5, GLuint slices = 25, GLuint stacks = 25); // Méthode qui initialise le modèle d'un cône

  void draw(QOpenGLShaderProgram& program, int attributeLocation); // Pour dessiner

  void bind();
  void release();

private:
  QGLBuffer vbo, ibo;
  GLuint vbo_sz;
  GLuint ibo_sz[3];
};

#endif



