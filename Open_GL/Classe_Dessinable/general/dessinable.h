#ifndef DESSINABLE_H
#define DESSINABLE_H
#include "../text/text_viewer.h"
#include <iostream>
class SupportADessin;

class Dessinable {
 public:
  Dessinable(): support(new TextViewer(TextViewer(cout))) {}
  Dessinable(SupportADessin* support): support(support) {}
  virtual ~Dessinable() {}
  virtual void dessine() = 0;
 protected:
  SupportADessin* support;
};

#endif