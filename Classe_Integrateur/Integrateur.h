#pragma once


class Integrateur{
   public: 
    virtual void evolue(Toupie const& T, const double dt) const = 0;
};

class IntegrateurEulerCromer : public Integrateur {
    public :
    virtual void evolue(Toupie const& T, const double dt) const override;
};