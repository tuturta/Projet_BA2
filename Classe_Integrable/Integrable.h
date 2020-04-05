#ifndef INTEGRABLE_H
#define INTEGRABLE_H

#include "../Open_GL/Classe_Dessinable/general/dessinable.h"
#include "../Classe_Vecteur/Vecteur.h"
#include "../Open_GL/Classe_Dessinable/general/support_a_dessin.h"

class Integrable : public Dessinable{ // Car Un integrable est dessinable(on a ses paramètres à chaque pas de temps)
   protected : 
    Vecteur P; // Vecteur de paramètres
    Vecteur P_point; // Dérivée temporelle des degrés de liberté
    Vecteur origine; //*****pour l'instant aucune autre info dessus...******

   public:
    //METHODES:
    Integrable(Vecteur P, Vecteur P_point, SupportADessin* support, Vecteur origine = {0,0,0})
    : Dessinable(support), P(P), P_point(P_point), origine(origine)  {} //CONSTRUCTEUR PAR DEFAUT POUR LE SUPPORT
    
    virtual Vecteur fonction_f() const = 0; //Equation du mouvement
    Vecteur getP() const;
    Vecteur getP_point() const;
    void setP(Vecteur const& autre);
    void setP_point(Vecteur const& autre);

};

#endif