#ifndef DESSINABLE_H
#define DESSINABLE_H

#include <array>

enum Couleur {blanc, noir, rouge, jaune, bleu, vert, violet, orange};
typedef std::array<double,3> RVBColor;


class SupportADessin;

class Dessinable {
 public:
  Dessinable(SupportADessin* support): support(support) {}
  virtual ~Dessinable() {}
  virtual void dessine() = 0;

protected:
  SupportADessin* support;
};

#endif
