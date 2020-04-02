#include "Integrateur.h"
#include <memory>
#include "../Open_GL/Classe_Dessinable/text/text_viewer.h"
#include <fstream>
//#include "../Classe_Toupie/Toupie.h"

using namespace std;

int main () {
    const unsigned int n(20);
    const double dt(0.01);
    double t(0);
    ofstream out;
    out.open("test.txt");
    TextViewer text(out);
    unique_ptr<SupportADessin> support_ptr(new TextViewer(text));
    Objet_en_chute_libre toupie(move(support_ptr),{0,1},{1.0,2.0},2.1);
    IntegrateurEulerCromer integrateur;
    Toupie* toupie_ptr(&toupie);
    unique_ptr<Toupie> toupie_ptr(new Objet_en_chute_libre(toupie)); //PB constructeur de copie
    unique_ptr<IntegrateurEulerCromer> int_ptr(new IntegrateurEulerCromer(integrateur));
    
    cout << " vitesse initiale "<< toupie.getP_point() <<endl;
    cout << " position initiale "<< toupie.getP() << endl;
    cout << "Retour de fonction_f() : " << toupie.fonction_f() << endl;
    

    for(size_t i(1); i<=n ;++i){
        t+=dt;
        int_ptr->evolue(toupie_ptr, dt);
        cout << endl << "=====TOUR " << i << "=====" << endl 
             << "t = " << t << endl
             << *(toupie_ptr) <<endl; 
    }
    return 0;   
}
