#pragma once
#include "../Classe_Toupie/Toupie.h"


class Integrateur{
   public: 
    void evolue(Toupie& T, double dt) const;
    void evolue_nfois(Toupie& T, double dt) const;

};

class IntegrateurEulerCromer : public Integrateur {
    public :
    void evolue(Toupie& T, double dt) const;
    void evolue_chute(Objet_en_chute_libre& O, double dt) const;
    void evolue_nfois(Toupie& T, double dt, unsigned int n) const;
    void evolue_chute_nfois(Objet_en_chute_libre& O, double dt, unsigned int n) const;
};