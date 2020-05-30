#pragma once
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"
#include <memory>
#include <iostream>

class Integrateur{
   public:
    virtual ~Integrateur() {} // Juste pour la forme (l'absence d'attributs assure normalement une destruction complète même sans la virtualité du destructeur)
    virtual void evolue(Toupie& T, const double dt) const = 0;
    virtual std::unique_ptr<Integrateur> copie() = 0;
};

class IntegrateurEulerCromer : public Integrateur {
   public :
    virtual void evolue(Toupie& T, const double dt) const override;
    virtual std::unique_ptr<Integrateur> copie() override;
    std::unique_ptr<IntegrateurEulerCromer> clone();

};

class IntegrateurNewmark : public Integrateur {
   public :
    virtual void evolue(Toupie& T, const double dt) const override;
    virtual std::unique_ptr<Integrateur> copie() override;
    std::unique_ptr<IntegrateurNewmark> clone();
};

class IntegrateurRungeKutta : public Integrateur {
   public :
    virtual void evolue(Toupie& T, const double dt) const override;
    virtual std::unique_ptr<Integrateur> copie() override;
    std::unique_ptr<IntegrateurRungeKutta> clone();
};
