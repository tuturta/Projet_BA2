#ifndef DESSINABLE_H
#define DESSINABLE_H
#include <memory>

class SupportADessin;

class Dessinable {
 public:
  /*Dessinable(unique_ptr<SupportADessin>&& support): support(move(support)) {}*/
  virtual ~Dessinable() {}
  virtual void dessine() = 0;

 protected:
  unique_ptr<SupportADessin> support;
};

#endif;