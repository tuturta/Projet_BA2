CXX = g++
CC = $(CXX)
TOUPIE =  ../Classe_Toupie/
VECTEUR = ../Classe_Vecteur/
MATRICE = ../Classe_Matrice/
CXXFLAGS = -std=c++11 -Wall

all: testIntegrateur

testIntegrateur : Integrateur.o testIntegrateur.o 

Integrateur.o: Integrateur.cc Integrateur.h ../Classe_Toupie/Toupie.h \
 ../Classe_Toupie/../Classe_Vecteur/Vecteur.h \
 ../Classe_Toupie/../Classe_Vecteur/../erreurs.h \
 ../Classe_Toupie/../Classe_Integrateur/Integrateur.h \
 ../Classe_Toupie/../Classe_Matrice/Matrice.h
testIntegrateur.o: testIntegrateur.cc ../Classe_Toupie/Toupie.h \
 ../Classe_Toupie/../Classe_Vecteur/Vecteur.h \
 ../Classe_Toupie/../Classe_Vecteur/../erreurs.h \
 ../Classe_Toupie/../Classe_Integrateur/Integrateur.h \
 ../Classe_Toupie/../Classe_Matrice/Matrice.h Integrateur.h