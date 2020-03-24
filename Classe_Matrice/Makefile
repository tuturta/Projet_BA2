CXX = g++
CC = $(CXX)
ADRESS =  ../Classe_Vecteur/
CXXFLAGS = -std=c++11 -Wall

all: testMatrice

testMatrice : Matrice.o testMatrice.o $(ADRESS)Vecteur.o

testMatrice.o: testMatrice.cc Matrice.h $(ADRESS)Vecteur.h $(ADRESS)erreurs.h
Matrice.o: testMatrice.cc Matrice.h $(ADRESS)Vecteur.h 
Vecteur.o : $(ADRESS)Vecteur.cc $(ADRESS)Vecteur.h 