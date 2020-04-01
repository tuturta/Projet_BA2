#include "Toupie.h"
#include "../erreurs.h"
#include "../Open_GL/Classe_Dessinable/text/text_viewer.h"
using namespace std;

int main() {
    try{
        TextViewer 
        ConeSimple cone1({0.0,0.0,0.0},{1.0,1.0,1.0},3.0,5.0,2.0);
        cout << cone1;
        Objet_en_chute_libre obj1({0.0,0.0,0.0},{1.0,1.0,1.0},3.0);
        cout << obj1;
        ConeSimple cone2((3),(1),1,-2,5);
        cout << cone2;
        Objet_en_chute_libre obj2({0.0,1.0}, {1.0,2.0},0.127);
        cout << obj2;

    }
    catch (Erreur& err) {
        cerr << "une erreur est survenue. ";
    }
    return 0;
}

