CXX = g++
CC = $(CXX)
ADRESS =  ../Classe_Vecteur/
CXXFLAGS = -std=c++11 -Wall

all: testToupie

testToupie : Toupie.o testToupie.o $(ADRESS)Vecteur.o
testToupie.o: testToupie.cc Toupie.h $(ADRESS)Vecteur.h ../erreurs.h
Toupie.o: Toupie.h $(ADRESS)Vecteur.h 
Vecteur.o : $(ADRESS)Vecteur.cc $(ADRESS)Vecteur.h