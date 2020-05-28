#define _USE_MATH_DEFINES //Pour régler le problème de M_PI non reconnu par le compilateur sur windows
#include <cmath>    
#include <iostream>
#include "../../constantes.h"
#include "Toupie.h"
#include "../Integrable.h"
#include "../../Classe_Vecteur/Vecteur.h"
#include "../../Classe_Matrice/Matrice.h"
#include "../../support_a_dessin.h"
using namespace std;

//=============================CLASSE TOUPIE===================================// 

// METHODES

ostream& Toupie::affiche_parametres(ostream& out) const {
    out << "Paramètre : " << P << endl;
    out << "Dérivée : " << P_point << endl;
    out << "Masse volumique (kg m-3) : " << masse_volumique << endl;
    return out;
}

unique_ptr<Toupie> Toupie::clone() const{
    return unique_ptr<Toupie>(new Toupie(*this));
}
unique_ptr<Toupie> Toupie::copie() const{
    return clone();
}
double Toupie::getHauteur() const{ return hauteur_;}
double Toupie::getRayon() const{ return rayon_;}

void Toupie::ajoute_position_CM() {
    positions_CM.push_back(vecteurOG());
}

std::vector<Vecteur> Toupie::getPositions_CM() const {
    return positions_CM;
}
Vecteur Toupie::ref_G_to_O_point(Vecteur const& point) const {
    return (S().inv()*point + point_de_contact +ref_G_to_O(vecteurAG()));
} 

void Toupie::update_A() {
    point_de_contact = vecteurOA();
} 

void Toupie::dessine() {
    support->dessine(*this);
} // Qu'est ce qu'on en fait ?

Vecteur Toupie::moment_poids() const{
    Vecteur poids(masse()*g); //dans le ref absolu
    poids=ref_O_to_G(poids);
    return vecteurAG()^poids;
}

// POUR LE CAS GENERAL : 

double Toupie::masse() const{
    double masse(0.0);
    for(size_t i(1) ; i <= N; ++i){
        masse += rayon2(i);
    }
    masse *= M_PI * masse_volumique * hauteur_ / N;
    return masse;
}

double Toupie::zi(size_t i) const{
    return (2.0*i-1)*hauteur_/(2.0*N);
}

double Toupie::rayon2(size_t i) const {  //TEMPORAIRE, DOIT ETRE REDEFINI DANS CHAQUE CLASSE
    cout << "APPEl TOUPIE::RAYON2()"<<endl;
    return pow(((zi(i)/hauteur_)*rayon_),2);
}


double Toupie::distanceBG() const{ // où O est l'origine du solide de construction et G le centre de masse
    double somme1(0.0), somme2(0.0);
    for(size_t i(1) ; i <= N; ++i){
                somme1 += rayon2(i) * zi(i); 
                somme2 += rayon2(i);
    }
    return somme1/somme2;
}

Vecteur Toupie::vecteurAG() const{ // TEMPORAIRE POUR PAS QUE LA TOUPIE SOIT VIRTUELLE
    //cout << "APPEL TOUPIE::vecteurAG()" << endl;
    return {0.0,0.0, distanceBG()};
}

Matrice Toupie::matrice_inertie_G() const {   // Matrice d'inertie au point A dans G calculé grace à la formule de Huygens-Steiner  
    
    double ri2(0.0); //représente ri^ (le rayon du solide de révolution à la hauteur zo). OPTIMISATION: RI2 permet d'éviter au programme à calculer 2 fois ri ^2 pour les deux sommes
    double somme1(0.0),somme2(0.0);
    for(size_t i(1) ; i <= N; ++i){
        ri2 = rayon2(i); //Pour éviter de calculer 2fois le rayon au carré
        somme1 += ri2*ri2;                  //Somme des ri^4 
        somme2 += pow(zi(i),2)* ri2;
    }
    double I3 (M_PI/2.0 * masse_volumique*somme1*hauteur_/N);
    double I1 (1.0/2.0*I3 + M_PI*masse_volumique*hauteur_/N*somme2 - masse()*pow(vecteurAG().norme(),2)); 
    Matrice IG (I1, I1, I3);
    return IG;

}

Matrice Toupie::matrice_inertie_A() const { 
    cout << "appel matrice inertie toupie" << endl;
    Vecteur AG(vecteurAG()); // Vecteur AG dans le ref G
    Matrice delta ( { pow(AG.coeff(1),2) + pow(AG.coeff(2),2) ,       -AG.coeff(0)*AG.coeff(1)          ,        -AG.coeff(0)*AG.coeff(2)        },
                    {       -AG.coeff(0)*AG.coeff(1)          , pow(AG.coeff(0),2) + pow(AG.coeff(2),2) ,         -AG.coeff(1)*AG.coeff(2)       }, 
                    {       -AG.coeff(0)*AG.coeff(2)          ,       -AG.coeff(1)*AG.coeff(2)          , pow(AG.coeff(0),2) + pow(AG.coeff(1),2)});

    return (matrice_inertie_G() + masse()*delta);
}

Vecteur Toupie::w() const{
    double theta(P.coeff(1));
    double psi_P(P_point.coeff(0));
    double theta_P(P_point.coeff(1));
    double phi_P(P_point.coeff(2));
    Vecteur w(3);
    double w1(theta_P);
    double w2(psi_P*sin(theta));
    double w3(psi_P*cos(theta)+phi_P);
    w = {w1,w2,w3}; 
    return w;
}

Vecteur Toupie::LA() const {
    return matrice_inertie_A()*w();
}

Vecteur Toupie:: vecteurOG() const{
    return (vecteurOA() + ref_G_to_O(vecteurAG()));
}

Vecteur Toupie:: vecteurOA() const{         //Pour le moment
    return Vecteur({0.0,0.0,0.0}); 
}

Vecteur Toupie::fonction_f() const{
    //cout << "--APPEL Toupie::fonction_f()--" << endl;
    return 2*P;
} //juste pour le test : à terme, fonction f de la toupie roulante

// SURCHARGES D'OPÉRATEURS 

ostream& operator<<(std::ostream& sortie, Toupie const& toupie) {
    return toupie.affiche_parametres(sortie);
}

//INVARIANTS :

double Toupie::produitMixte_awL() const{
    return (w()^(matrice_inertie_G()*w())).coeff(2);
}

double Toupie::energie_totale() const{
    return ((w()*LA())/2.0 - masse()*(vecteurOG()*g));
}

double Toupie::LAz() const{                            
    return ref_G_to_O(LA()).coeff(2);                 // Retourne la composante z de LA exprimé dans cette nouvelle base  //Change la base du moment cinétique au point A (noté LA): Referentiel Inertie G --> Referentiel Galiléen O
}

double Toupie::LA3() const{        
   return LA().coeff(2);        //La matrice d'inertie étant exprimé dans le ref inertiel G, cela renvoie LA3 : 3eme composante du Moment cinétique au point A
}




//=============================CLASSE CONE SIMPLE===================================//

//METHODES:

ostream& ConeSimple::affiche_parametres(ostream& out) const {
    out << "CONIQUE SIMPLE " << endl;
    Toupie::affiche_parametres(out);
    out << "Hauteur (m) : " << hauteur_ << endl;
    out << "Rayon   (m) : " << rayon_ << endl;
    out << "Point de contact (A) : " << point_de_contact << endl;
    return out;
}

double ConeSimple::masse() const{ //masse calculé grace a la formule p8
    return (1.0/3.0)*M_PI*masse_volumique*pow(rayon_,2)*hauteur_;
}


Matrice ConeSimple::matrice_inertie_G() const { // Matrice d'inertie calculé grace a la formule p8
    double I1, I3;
    I1 = (3.0*masse()/20)*(pow(rayon_,2)+ 1.0/4.0*pow(hauteur_,2));
    I3 = (3.0/10.0)*masse()*pow(rayon_,2);
    return Matrice(I1, I1, I3);
}

unique_ptr<ConeSimple> ConeSimple::clone() const{
    return unique_ptr<ConeSimple>(new ConeSimple(*this));
}
unique_ptr<Toupie> ConeSimple::copie() const{
    return clone();
}


Vecteur ConeSimple::vecteurAG() const{ // Centre de masse dans le ref d'inertie G vu depuis le point de contact
    return {0,0, (3.0/4.0)*hauteur_};
}


Vecteur ConeSimple::fonction_f() const{ //(Cf cadre rouge page 12) //avec P= psi-theta-phi
    //cout << "-----appel ConeSimple::fonction()-----" << endl;
    //Pour la lisibilité :
    double theta(P.coeff(1));
    double psi_P(P_point.coeff(0));
    double theta_P(P_point.coeff(1));
    double phi_P(P_point.coeff(2));
    //cout << "P=" << P << endl;
    //1.CALCUL DE w dans RG (repère d'inertie)
    //cout << "MA_G = " << moment_poids() << endl;
    //cout << "w_G = " << w() << endl;

    //2.CALCUL DE W_POINT: (dans Repère d'inertie)
    Vecteur w_point(3);
    Vecteur we(w());
    we.set_coord(2,we.coeff(2) - phi_P); //rotation du repère (ne prend pas en compte la rotation propre de la toupie
    w_point = matrice_inertie_A().inv()*(moment_poids()-(we^(matrice_inertie_A()*w())));
    std::cout << "Dw_G= " << w_point << std::endl; //1er tour bon après non

    //3.CALCUL DE P_POINT_POINT: 
    Vecteur P_point_point(3);
    P_point_point.set_coord(1, w_point.coeff(0)); //Calcul de théta point point
    
    if(abs(theta) < eps){ //test theta=0.0
        P_point_point.set_coord(2,w_point.coeff(2)); //Modification de phi point point = w3point formule (2) p6
    }else{
        P_point_point.set_coord(0, (w_point.coeff(1) - psi_P*theta_P*cos(theta)) / sin(theta) ); //Modification psi point point : formule (2) p6
        P_point_point.set_coord(2, w_point.coeff(2) - P_point_point.coeff(0)*cos(theta) + psi_P*theta_P*sin(theta)); //Modification phi point point formule (2) p6
    }

    std::cout << "DDpsi =" << P_point_point.coeff(0) << std::endl;
    std::cout << "DDtheta =" << P_point_point.coeff(1) << std::endl;
    std::cout << "DDphi =" << P_point_point.coeff(2) << std::endl;

    //4.CALCUL DE G:
    //Pour le moment on le fait pas car on considère qu'il n'y a pas de glissement Va = 0

    return P_point_point;
}



// Méthode virtuelle dessinable

void ConeSimple::dessine() {
    support->dessine(*this);
} 

//============================CLASSE OBJ CHUTE==========================================//

void Objet_en_chute_libre::dessine() {
    support->dessine(*this);
}

Vecteur Objet_en_chute_libre::fonction_f() const{
        return {0,-9.81,0.0};
}

unique_ptr<Objet_en_chute_libre> Objet_en_chute_libre::clone() const{
    return unique_ptr<Objet_en_chute_libre>(new Objet_en_chute_libre(*this));
}
unique_ptr<Toupie> Objet_en_chute_libre::copie() const{
    return clone();
}

//=============================CLASSE CONE GENERAL=======================================//


Vecteur ConeGeneral::fonction_f() const{
   // cout << "--APPEL ConeGeneral::fonction_f()--" <<endl;
    
    //Lisibilité:
    double theta(P.coeff(1));
    double psi_P(P_point.coeff(0));
    double theta_P(P_point.coeff(1));
    double phi_P(P_point.coeff(2));
    
    //1.CALCUL DE w et MA dans RG (repère d'inertie)
        
        //Methode w()
    Vecteur MA(masse()*(g.norme())*(distanceBG()*sin(theta)),0,0); // On considère que seul le poids agit sur la toupie, on néglige les autres forces  
    //cout << "MA_G = " << MA << endl;
    //cout << "w_G = " << w() << endl;

    //2.Calcul de IA avec Huygens-Steiner

    //methode matrice_inertie_A()

    //3.CALCUL DE W_POINT: (dans Repère d'inertie)
    Vecteur w_point(3);
    Vecteur we(w());
    we.set_coord(2,we.coeff(2) - phi_P); //rotation du repère (ne prend pas en compte la rotation propre de la toupie
    w_point = matrice_inertie_A().inv()*(MA-(we^(matrice_inertie_A()*w())));
    //std::cout << "Dw_G= " << w_point << std::endl; //1er tour bon après non
    
    //4.CALCUL DE P_POINT_POINT: 
    Vecteur P_point_point(3);
    P_point_point.set_coord(1, w_point.coeff(0)); //Calcul de théta point point
    
    if(abs(theta) < eps){ //test theta=0.0
        P_point_point.set_coord(2,w_point.coeff(2)); //Modification de phi point point = w3point formule (2) p6
    }else{
        P_point_point.set_coord(0, (w_point.coeff(1) - psi_P*theta_P*cos(theta)) / sin(theta) ); //Modification psi point point : formule (2) p6
        P_point_point.set_coord(2, w_point.coeff(2) - P_point_point.coeff(0)*cos(theta) + psi_P*theta_P*sin(theta)); //Modification phi point point formule (2) p6
    }

    //std::cout << "DDpsi =" << P_point_point.coeff(0) << std::endl;
    //std::cout << "DDtheta =" << P_point_point.coeff(1) << std::endl;
    //std::cout << "DDphi =" << P_point_point.coeff(2) << std::endl;

    
    //5.CALCUL DE G:
        //Pour le moment on le fait pas car on considère qu'il n'y a pas de glissement Va = 0

    return P_point_point;
}

Vecteur ConeGeneral::vecteurAG() const{
    return {0.0,0.0,distanceBG()};
}

unique_ptr<ConeGeneral> ConeGeneral::clone() const{
    return unique_ptr<ConeGeneral>(new ConeGeneral(*this));
}
unique_ptr<Toupie> ConeGeneral::copie() const{
    return clone();
}

double ConeGeneral::rayon2(size_t i) const {
    return pow((zi(i)/hauteur_ *rayon_),2);
}

//=============================CLASSE TOUPIE ROULANTE===================================//


Vecteur ToupieRoulante::fonction_f() const{
    //cout << "--APPEL ToupieRoulante::fonction_f()--" <<endl;
    
    //Lisibilité:
    double theta(P.coeff(1));
    double psi_P(P_point.coeff(0));
    double theta_P(P_point.coeff(1));
    double phi_P(P_point.coeff(2));
 
    //cout << "psi = " << psi << endl;
    //cout << "theta = " << theta << endl;
    //cout << "Dpsi = " << psi_P << endl;
    //cout << "Dtheta = " << theta_P << endl;
    //cout << "Dphi = " << phi_P << endl;

    
    //1.CALCUL DE w et MA dans RG (repère d'inertie)
        
    //On utilise la méthode w()
    Vecteur MA(masse()*(g.norme())*(vecteurAG().norme())*sin(theta),0.0,0.0); // On considère que le poids est la seule force appliquée ailleurs qu'en A
    //cout << "MA_G = " << MA << endl;
    //cout << "w_G = " << w() << endl;

    //2.Calcul de IA avec Huygens-Steiner

       //methode matrice_inertie_A()
    Matrice IA(matrice_inertie_A());
    
    //3.CALCUL DE W_POINT: (dans Repère d'inertie)
    
    Vecteur w_point(3);
    Vecteur we(w());
    we.set_coord(2,we.coeff(2) - phi_P); //rotation du repère (ne prend pas en compte la rotation propre de la toupie
    w_point = matrice_inertie_A().inv()*(MA-(we^(matrice_inertie_A()*w())));
    // cout << "matrice inertie.inv() " << (matrice_inertie_A().inv()) << endl;
    //cout << "Dw_G= " << w_point << endl;
    
    //4.CALCUL DE P_POINT_POINT: 
    Vecteur P_point_point(6);
    P_point_point.set_coord(1, w_point.coeff(0)); //Calcul de théta point point
    
    if(abs(theta) < eps){ //test theta=0.0
        P_point_point.set_coord(2,w_point.coeff(2)); //Modification de phi point point = w3point formule (2) p6
    }else{
        P_point_point.set_coord(0, (w_point.coeff(1) - psi_P*theta_P*cos(theta)) / sin(theta) ); //Modification psi point point : formule (2) p6
        P_point_point.set_coord(2, w_point.coeff(2) - P_point_point.coeff(0)*cos(theta) + psi_P*theta_P*sin(theta)); //Modification phi point point formule (2) p6
    }

    //cout << "P point point en sortie de  f() : " << P_point_point << endl;

    //5.CALCUL DE LA POSITION DE G:

    Vecteur vg( -ref_G_to_O(vecteurAG())^w() ); //Vg=AG^w dans un solide

    //Dérivées de Gx,Gy,Gz (P4_point_point, P5_point_point, P6_point_point
    P_point_point.set_coord(3,vg.coeff(0));
    P_point_point.set_coord(4,vg.coeff(1));
    P_point_point.set_coord(5,vg.coeff(2));

    //6.CALCUL DE LA POSITION DE A:

    //méthode avec les points du profil de révolution etc -> selon le complément,trop ambitieuse.
    //nous nous contentons donc de fournir la position du point de contact d'une toupie
    //chinoise à chaque instant, car c'est la seule chose qui nous manque pour la dessiner
    //-->méthode extérieure pour actualiser
    
    return P_point_point;
}

Vecteur ToupieRoulante::vecteurAG() const{ // /!\ POUR UNE TOUPIE CHINOISE
    Vecteur AC (ref_O_to_G({0.0,0.0,rayon_}));
    return (AC - vecteurGC()); // AG dans le ref G
}

double ToupieRoulante::rayon2(size_t i) const {
    return (2.0*rayon_*zi(i) -  pow(zi(i),2));
}

void ToupieRoulante::update_A() { // /!\ POUR UNE TOUPIE CHINOISE
    //point C en coord absolues
    Vecteur C(ref_G_to_O_point(vecteurGC()));
    //AC=R*k et C est de coord nulle selon k :
    setPoint_de_contact({C.coeff(0), C.coeff(1), 0.0}); // Point de contact dans le ref absolu
}

Vecteur ToupieRoulante::vecteurGC() const{ //  /!\POUR UNE TOUPIE CHINOISE
    //cout << "appel ToupieRoulante::VecteurGC()" << endl;
    return {0.0,0.0, rayon_ - distanceBG()}; // dans le ref G
}

/* PAS BESOIN POUR L'INSTANT
Vecteur ToupieRoulante::vecteurOB() const{ // /!\ POUR UNE TOUPIE CHINOISE
    Vecteur OG({P_point.coeff(3), P_point.coeff(4), P_point.coeff(5)}); // Dans le ref O
    Vecteur GB(ref_G_to_O({0.0,0.0,-distanceBG()}));  // Dans le ref O        
    Vecteur OB(OG+GB);    
    return OB ;
}
*/

unique_ptr<ToupieRoulante> ToupieRoulante::clone() const{
    return unique_ptr<ToupieRoulante>(new ToupieRoulante(*this));
}
unique_ptr<Toupie> ToupieRoulante::copie() const{
    return clone();
}


//=============================CLASSE TOUPIE CHINOISE===================================//

ostream& ToupieChinoise::affiche_parametres(ostream& out) const {
    out << " CHINOISE " << endl;
    Toupie::affiche_parametres(out);
    out << "Hauteur tronquée (m) : " << hauteur_ << endl;
    out << "Rayon (m) : " << rayon_ << endl;
    out << "Point de contact (A) : " << point_de_contact << endl;
    return out;
}

double ToupieChinoise::masse() const{
    return (M_PI*masse_volumique*((4.0/3.0)*pow(rayon_,3) - hauteur_*hauteur_*(rayon_-(1.0/3.0)*hauteur_)));
}

double ToupieChinoise::alpha() const{
    return (3.0*pow(hauteur_,2)/(4.0*rayon_*(rayon_ + hauteur_)));
}

Vecteur ToupieChinoise::vecteurGC() const{
    return {0.0, 0.0, rayon_*alpha()};
}

Matrice ToupieChinoise::matrice_inertie_G() const{
    //cout << "APPEL Toupiechinoise::matrice_inertie_A()" << endl;
    
    double I3 ((M_PI/30.0)*masse_volumique*pow((2.0*rayon_-hauteur_),3)*(2.0*pow(rayon_,2)+3.0*hauteur_*rayon_+3.0*pow(hauteur_,2)));
    double I1 ((1.0/2.0)*I3 + ((M_PI/15.0)*masse_volumique*pow((2.0*rayon_-hauteur_),2)*(pow(rayon_,3)+ hauteur_*pow(rayon_,2) - 3.0*pow(hauteur_,2)*rayon_+3.0*pow(hauteur_,3))) -masse()*vecteurGC().norme2());
    return Matrice(I1,I1,I3);
}

Vecteur ToupieChinoise::fonction_f() const{   
    //cout << "APPEL ToupieChinoise::fonction_f()" << endl;
    cout << "Energie totale: " << energie_totale() << endl
         << "LA_z = " << LAz() << endl
         << "LA3 = " << LA3() << endl
         << "produit mixte = " << produitMixte_awL() << endl;

    double psi(P.coeff(0));
    double theta(P.coeff(1));
    double psi_p(P_point.coeff(0));
    double theta_p(P_point.coeff(1));
    double phi_p(P_point.coeff(2));
    double I1((matrice_inertie_G()*Vecteur({1.0,0.0,0.0})).coeff(0));
    double I3((matrice_inertie_G()*Vecteur({0.0,0.0,1.0})).coeff(2));
    double f1(phi_p + psi_p*cos(theta));    
    double f3( I1*I3 +masse()*pow(rayon_,2)*I1*pow(sin(theta),2) + masse()*pow(rayon_,2)*I3*pow( (alpha()-cos(theta)),2 ) );
    double f2( (theta_p/sin(theta))*f1* (I3*(I3 + masse()*pow(rayon_,2)* (1.0-alpha()*cos(theta))))/f3 -(2.0*psi_p*theta_p)/tan(theta) );


    Vecteur P_p_p(5); // Vecteur P_point_point que l'on veut calculer et retourner, initalisé à (0,0,0,0,0)
    
    if (abs(theta) < eps){ // Dans le cas ou theta = 0, on rajoute un petit angle pour ("approcher la solution"). De plus, cela simule aussi l'équilibre instable en theta = 0 (pas franchement notre volonté première... )
        if(theta<0.0){
            theta -= 100*eps;
        }else{
            theta += 100*eps;
        }
    }


    // Psi_point_point
    P_p_p.set_coord(0,  f2);
   
    // Theta_point_point
    //cout << "1er terme de theta_p_p: " << (sin(theta)/(I1+masse()*pow(rayon_,2)*(pow((alpha() - cos(theta)),2) + pow(sin(theta),2)))) << endl;
    P_p_p.set_coord(1,  (sin(theta)/(I1+masse()*pow(rayon_,2)*(pow(alpha() - cos(theta),2) + pow(sin(theta),2))))
                        *(pow(psi_p,2)*(-masse()*pow(rayon_,2)*(alpha()-cos(theta))*(1.0-alpha()*cos(theta)) + I1*cos(theta)) 
                        + f1*psi_p*(masse()*pow(rayon_,2)*(alpha()*cos(theta) - 1.0) - I3) - masse()*pow(rayon_*theta_p,2)*alpha() + masse()*rayon_*alpha()*g.coeff(2))  );
    
    // Phi_point_point
    P_p_p.set_coord(2,  psi_p*theta_p*sin(theta)-cos(theta)*f2 
                        - f1*theta_p*sin(theta)*(masse()*pow(rayon_,2)*(I3*(alpha()-cos(theta)) + I1*cos(theta)))/f3    );  
    
    // Cx: composante en x du milieu C de la sphère dans le repère O
    P_p_p.set_coord(3,  rayon_*(theta_p*sin(psi) - phi_p*cos(psi)*sin(theta)) );
    
    // Cy: composante en y du milieu C de la sphère dans le repère O
    P_p_p.set_coord(4,  -rayon_*(theta_p*cos(psi)+phi_p*sin(psi)*sin(theta)));

    //cout << "Vecteur P_p_p: " << P_p_p << endl;
    return P_p_p;
    
}

unique_ptr<ToupieChinoise> ToupieChinoise::clone() const{
    return unique_ptr<ToupieChinoise>(new ToupieChinoise(*this));
}
unique_ptr<Toupie> ToupieChinoise::copie() const{
    return clone();
}


// INVARIANTS :

/*
double ConeSimple::energie_totale() const{
    Vecteur La(matrice_inertie_A()*w());
    Vecteur g_(g);
    ref_O_to_G(g_); // Le centre de masse est exprimé dans le ref G donc on doit exprimer aussi g_ dans G avant de faire le produit scalaire (sachant que la constante g est exprimé de base dans le ref galiléen O)
    return (w()*La)/2.0 - masse()*(g_*vecteurAG());
}

double ConeSimple::LAz() const{        
    Vecteur La(matrice_inertie_A()*w());
    ref_G_to_O(La);                     //Change la base du moment cinétique au point A (noté LA): Referentiel Inertie G --> Referentiel Galiléen O
    return La.coeff(2);                 // Retourne la composante z de LA exprimé dans cette nouvelle base
}

double ConeSimple::LA3() const{        
   return (matrice_inertie_A()*w()).coeff(2);        //La matrice d'inertie étant exprimé dans le ref inertiel G, cela renvoie LA3 : 3eme composante du Moment cinétique au point A
}

double ConeSimple::produitMixte_awL() const{
    return (w()^(matrice_inertie_A()*w())).coeff(2);
}
*/


double ToupieChinoise::distanceBG() const{
    return (rayon_*(1.0-alpha()) );
}


Vecteur ToupieChinoise::vecteurOA() const{
    return {P_point.coeff(3), P_point.coeff(4), 0.0};
}