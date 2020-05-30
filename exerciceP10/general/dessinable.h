#ifndef DESSINABLE_H
#define DESSINABLE_H

#include "erreurs.h"
#include <array>
#include <iostream>


enum Couleur {blanc, noir, rouge, jaune, bleu, vert, violet, orange};
typedef std::array<double,3> RVBColor;

class SupportADessin;

class Dessinable {
 public:
  Dessinable(SupportADessin* support): support(support) {
    if (support==nullptr) {
      Erreur err = {"Le support doit exister..."};
      throw err;
    }
  }
  virtual ~Dessinable() {} // pas delete support : on n'a pas alloué de la mémoire ici !

  virtual void dessine() = 0;

protected:
  SupportADessin* support;
};

#endif
