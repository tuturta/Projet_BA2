#pragma once
#include "../Classe_Toupie/Toupie.h"
#include <memory>


class Integrateur{
   public: 
    virtual void evolue(unique_ptr<Toupie> const& T, const double dt) const = 0;
};

class IntegrateurEulerCromer : public Integrateur {
    public :
    virtual void evolue(unique_ptr<Toupie> const& T, const double dt) const override;
};