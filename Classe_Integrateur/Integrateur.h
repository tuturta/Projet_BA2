#pragma once
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"


class Integrateur{
   public: 
    virtual void evolue(Toupie& T, const double dt) const = 0;
};

class IntegrateurEulerCromer : public Integrateur {
    public :
    virtual void evolue(Toupie& T, const double dt) const override;
};