#pragma once
#ifndef TEXT_VIEWER_H
#define TEXT_VIEWER_H

#include <iostream>
#include "../general/support_a_dessin.h"

class TextViewer : public SupportADessin {
 public:
 TextViewer(std::ostream& flot)
    : flot(flot)
  {}
  virtual ~TextViewer() {}
  //Les methodes sont à modifier histoire que leurs sorties puissent être lu par gnu plot
  virtual void dessine(ConeSimple const& objet) override;
  virtual void dessine(Objet_en_chute_libre const& objet) override;
  virtual void dessine(Toupie const& objet) override;
    //virtual void dessine(Systeme const& objet) override;

 private:
  std::ostream& flot;
};

#endif
