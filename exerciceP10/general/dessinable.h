#ifndef DESSINABLE_H
#define DESSINABLE_H
#include <memory>

class SupportADessin;


class Dessinable {
 public:
 // Dessinable(): support(new TextViewer(TextViewer(std::cout))) {}
  Dessinable(SupportADessin* support): support(support) {}
  virtual ~Dessinable() {}
  virtual void dessine() = 0;
  void setSupport(SupportADessin* nouveau_support) {support = nouveau_support;} // Permet de modifier le support dans le constructeur de GLWidget
 // virtual std::unique_ptr<Dessinable> copieDessinable() const =0;
 protected:
  SupportADessin* support;
};

#endif
