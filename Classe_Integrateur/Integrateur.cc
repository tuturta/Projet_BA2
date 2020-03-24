#include "Integrateur.h"
#include "../Classe_Toupie/Toupie.h"



void IntegrateurEuleurCromer::evolue(Toupie& T, double dt) const {
        t.P_point = t.P_point + dt*t.fonction_f();
        t.P = t.P + dt*t.P;
    }

void evolue_nfois(Toupie& T, double dt, unsigned int n) const;
