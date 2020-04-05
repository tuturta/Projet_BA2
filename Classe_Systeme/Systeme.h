#include <vector>
#include <memory>
#include <iostream>
#include "../Open_GL/Classe_Dessinable/general/dessinable.h"
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../Classe_Integrateur/Integrateur.h"

class Systeme : public Dessinable{
   protected :
    std::vector<std::unique_ptr<Toupie>> objets; //classe hétérogène de Toupie(plus tard d'Intégrables)
    IntegrateurEulerCromer integrateur; // Integrateur propre au système
   public :
    void evolue(const double dt);
    //Pas de constructeur par défaut pour le moment
    std::ostream& affiche(std::ostream& out) const;

    virtual void dessine() override;

};

std::ostream& operator<<(std::ostream& out, Systeme const& S);