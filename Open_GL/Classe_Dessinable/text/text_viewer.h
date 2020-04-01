#ifndef TEXT_VIEWER_H
#define TEXT_VIEWER_H

#include <iostream>
#include "general/support_a_dessin.h"

class TextViewer : public SupportADessin {
 public:
 TextViewer(std::ostream& flot)
    : flot(flot)
  {}
  virtual ~TextViewer() {}

  virtual void dessine(ConeSimple const&) override;
  virtual void dessine(Objet_en_chute_libre const&) override;
  virtual void dessine(Systeme const&) override;


 private:
  std::ostream& flot;
};

#endif