#include "Integrateur.h"
#include "../Classe_Integrable/Integrable.h"
#include "../Classe_Integrable/Classe_Toupie/Toupie.h"
#include "../Classe_Vecteur/Vecteur.h" // Pour les produits entre vecteurs
#include "../Classe_Systeme/Systeme.h"
#include "../constantes.h"

using namespace std;


void IntegrateurEulerCromer::evolue(Toupie& T, const double dt) const {
        T.setP_point(T.getP_point() + dt*((T.copie())->fonction_f())); //PROBLEME : l'appel est fait directement à Toupie::fonction(); sans tenir compte du masquage de ObjetEnChuteLibre::fonction();
        /*std::cout << "Dpsi = " << T.getP_point().coeff(0) << std::endl;
        std::cout << "Dtheta = " << T.getP_point().coeff(1) << std::endl;
        std::cout << "Dphi = " << T.getP_point().coeff(2) << std::endl;*/

        T.setP(T.getP() + dt*((T.copie())->getP_point()));

        /*std::cout << "dans evolue Toupie : " << std::endl << "psi = " << T.getP().coeff(0) << std::endl;
        std::cout << "theta = " << T.getP().coeff(1) << std::endl;
        std::cout << "phi = " << T.getP().coeff(2) << std::endl << std::endl;*/

        T.ajoute_position_CM(); // ajoute cette nouvelle position du CM dans le vector nécessaire pour la trace
}

void IntegrateurEulerCromer::evolue(Systeme& S, const double dt) const {
    for(size_t i(0) ; i < S.size() ; ++i){
            unique_ptr<Toupie> temp(S.getToupie(i));
            evolue(*temp,dt);
            S.setToupie(i, *temp);
    }
}
void IntegrateurNewmark::evolue(Toupie& T, const double dt) const {
        Vecteur q(3);
        Vecteur r(3);
        Vecteur s(3); //initialise 3 vecteurs nuls à trois dimensions 

        s=T.copie()->fonction_f();
        Vecteur diff(T.getP()-q);
        const Vecteur P_point_temp(T.getP_point());
        const Vecteur P_temp(T.getP());

        do {
                q=T.getP();
                r=T.copie()->fonction_f();
                T.setP_point(P_point_temp+(dt/2.0)*(r+s));
                T.setP(P_temp+dt*P_point_temp+(dt*dt/3.0)*(0.5*r+s));
                diff=T.getP()-q;

        } while (diff.norme()>=eps);

        T.ajoute_position_CM(); // ajoute cette nouvelle position du CM dans le vector nécessaire pour la trace

}

void IntegrateurNewmark::evolue(Systeme& S, const double dt) const {
        for(size_t i(0) ; i < S.size() ; ++i){
            unique_ptr<Toupie> temp(S.getToupie(i));
            evolue(*temp,dt);
            S.setToupie(i, *temp);
        }
}  ///un moyen de pas faire du copié-coller ?...

void IntegrateurRungeKutta::evolue(Toupie& T, const double dt) const {

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
        k1_p=T.copie()->fonction_f();

        k2=P_point_temp+dt/2.0*k1_p;
        T.setP(P_temp+dt/2.0*k1);
        T.setP_point(k2);
        k2_p=T.copie()->fonction_f();

        k3=P_point_temp+dt/2.0*k2_p;
        T.setP(P_temp+dt/2.0*k2);
        T.setP_point(k3);
        k3_p=T.copie()->fonction_f();

        k4=P_point_temp+dt*k3_p;
        T.setP(P_temp+dt*k3);
        T.setP_point(k4);
        k4_p=T.copie()->fonction_f();

        T.setP(P_temp+dt/6.0*(k1+2*k2+2*k3+k4));
        T.setP_point(P_point_temp+dt/6.0*(k1_p+2*k2_p+2*k3_p+k4_p));

        T.ajoute_position_CM(); // ajoute cette nouvelle position du CM dans le vector nécessaire pour la trace
        
}

void IntegrateurRungeKutta::evolue(Systeme& S, const double dt) const {
        for(size_t i(0) ; i < S.size() ; ++i){
            unique_ptr<Toupie> temp(S.getToupie(i));
            evolue(*temp,dt);
            S.setToupie(i, *temp);
        }
} ///copié-collé.../


