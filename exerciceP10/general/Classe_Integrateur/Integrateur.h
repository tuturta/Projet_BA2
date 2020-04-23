#pragma once
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../Classe_Systeme/Systeme.h"
#include "../dessinable.h"


class Integrateur{
   public: 
    virtual void evolue(Dessinable& D, const double dt) const = 0; // POur GLWidget: permet de pouvoir écrire integratuer.evolue(dessinable..) dans glwidget.cc mais la méthode ne sera jamais appelé
    virtual void evolue(Toupie& T, const double dt) const = 0;
    virtual void evolue(Systeme& S, const double dt) const = 0;

};

class IntegrateurEulerCromer : public Integrateur {
    public :
    virtual void evolue(Dessinable& D, const double dt) const override;
    virtual void evolue(Toupie& T, const double dt) const override;
    virtual void evolue(Systeme& S, const double dt) const override;
};
