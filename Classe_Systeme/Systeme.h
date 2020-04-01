#pragma once
#include "../Open_GL/Classe_Dessinable/general/dessinable.h"
#include "../Classe_Toupie/Toupie.h"
#include "../Classe_Integrateur/Integrateur.h"
#include <vector>
#include <memory>

class Systeme : public Dessinable {
   protected :
    std::vector<std::unique_ptr<Toupie>> objets; //classe hétérogène de Toupie
    IntegrateurEulerCromer integrateur; // Integrateur propre au système
    double dt; //Pas de temps
   public :
    void evolue();
    //Pas de constructeur par défaut pour le moment
    std::ostream& affiche(std::ostream& out) const;
};

std::ostream& operator<<(std::ostream& out, Systeme const& S);