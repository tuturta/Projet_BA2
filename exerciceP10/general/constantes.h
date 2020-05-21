#pragma once
#include "Classe_Vecteur/Vecteur.h"

extern const Vecteur g; //vecteur accélération gravité
extern const double eps; //epsilon --à la fin du projet, si on ne l'a pas utilisée ailleurs, détruire ça et la mettre direct dans la méthode correctif_0 de la classe vecteur 
extern const double N; //Nombre de tranche pour construire notre solide de revolution (précision de la construction)