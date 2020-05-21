#pragma once
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../Classe_Systeme/Systeme.h"

//ESSAI ARTHUR *****************************************
//#include "../dessinable.h"


class Integrateur{
   public:
    virtual void evolue(Toupie& T, const double dt) const = 0;
    virtual void evolue(Systeme& S, const double dt) const = 0;

};

class IntegrateurEulerCromer : public Integrateur {
    public :
    virtual void evolue(Toupie& T, const double dt) const override;
    virtual void evolue(Systeme& S, const double dt) const override;
};

class IntegrateurNewmark : public Integrateur {
    public :
    virtual void evolue(Toupie& T, const double dt) const override;
    virtual void evolue(Systeme& S, const double dt) const override;

};

class IntegrateurRungeKutta : public Integrateur {
    public :
    virtual void evolue(Toupie& T, const double dt) const override;
    virtual void evolue(Systeme& S, const double dt) const override;
};