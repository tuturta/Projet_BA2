#ifndef CONTENU_H
#define CONTENU_H

#include "dessinable.h"
#include "support_a_dessin.h"

class Contenu : public Dessinable {
public:
  Contenu(SupportADessin* vue)
    : Dessinable(vue)
  {}
  virtual ~Contenu() {}

  virtual void dessine() override
  { support->dessine(*this); }
};

#endif // CONTENU_H
