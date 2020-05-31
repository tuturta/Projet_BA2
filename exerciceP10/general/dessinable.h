#ifndef DESSINABLE_H
#define DESSINABLE_H

#include "erreurs.h"

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
