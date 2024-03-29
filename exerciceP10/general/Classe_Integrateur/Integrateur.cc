#include "Integrateur.h"
#include "../Classe_Integrable/Integrable.h"
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../Classe_Vecteur/Vecteur.h" // Pour les produits entre vecteurs
#include "../constantes.h"

#include <memory>

using namespace std;


void IntegrateurEulerCromer::evolue(Integrable& T, const double dt) const {
        T.setP_point(T.getP_point() + dt*(T.fonction_f()));
        T.setP((T.getP() + dt*(T.getP_point())));
        T.ajoute_position_CM(); // ajoute cette nouvelle position du CM ds le vector nécessaire pour la trace
        T.update_A(); // mise à jour des coordonnées du point de contact
}

void IntegrateurNewmark::evolue(Integrable& T, const double dt) const {
        size_t dimension((T.getP()).dim());
        Vecteur q(dimension);
        Vecteur r(dimension);
        Vecteur s(dimension); // Initialisation 3 variables de type Vecteur nulles de bonne dimension 

        s=T.fonction_f();
        Vecteur diff(T.getP()-q);
        const Vecteur P_point_temp(T.getP_point());
        const Vecteur P_temp(T.getP());

        do {
                q=T.getP();
                r=T.fonction_f();
                T.setP_point(P_point_temp+(dt/2.0)*(r+s));
                T.setP(P_temp+dt*P_point_temp+(dt*dt/3.0)*(0.5*r+s));
                diff=T.getP()-q;

        } while (diff.norme()>=eps);

        T.ajoute_position_CM();
        T.update_A();
}

void IntegrateurRungeKutta::evolue(Integrable& T, const double dt) const {

        //Variables nécessaires :
        Vecteur P_temp(T.getP()); 
        Vecteur P_point_temp(T.getP_point()); 
        Vecteur k1(3);
        Vecteur k2(3);
        Vecteur k3(3);
        Vecteur k4(3);
        Vecteur k1_p(3);
        Vecteur k2_p(3);
        Vecteur k3_p(3);
        Vecteur k4_p(3);

        //Intégration :
        k1=P_point_temp;
        k1_p=T.fonction_f();

        k2=P_point_temp+dt/2.0*k1_p;
        T.setP(P_temp+dt/2.0*k1);
        T.setP_point(k2);
        k2_p=T.fonction_f();

        k3=P_point_temp+dt/2.0*k2_p;
        T.setP(P_temp+dt/2.0*k2);
        T.setP_point(k3);
        k3_p=T.fonction_f();

        k4=P_point_temp+dt*k3_p;
        T.setP(P_temp+dt*k3);
        T.setP_point(k4);
        k4_p=T.fonction_f();

        T.setP(P_temp+dt/6.0*(k1+2*k2+2*k3+k4));
        T.setP_point(P_point_temp+dt/6.0*(k1_p+2*k2_p+2*k3_p+k4_p));

        T.ajoute_position_CM(); // ajoute cette nouvelle position du CM dans le vector nécessaire pour la trace
        T.update_A();        
}

// COPIE POLYMORPHIQUE DES INTÉGRATEURS :

unique_ptr<Integrateur> IntegrateurEulerCromer::copie() {
        return clone();
}
unique_ptr<IntegrateurEulerCromer> IntegrateurEulerCromer::clone() {
        return unique_ptr<IntegrateurEulerCromer>(new IntegrateurEulerCromer(*this));
}

unique_ptr<Integrateur> IntegrateurNewmark::copie() {
        return clone();
}
unique_ptr<IntegrateurNewmark> IntegrateurNewmark::clone() {
        return unique_ptr<IntegrateurNewmark>(new IntegrateurNewmark(*this));
}

unique_ptr<Integrateur> IntegrateurRungeKutta::copie() {
        return clone();
}
unique_ptr<IntegrateurRungeKutta> IntegrateurRungeKutta::clone() {
        return unique_ptr<IntegrateurRungeKutta>(new IntegrateurRungeKutta(*this));
}

