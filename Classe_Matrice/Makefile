CXX = g++
CC = $(CXX)
CXXFLAGS = -std=c++11 -Wall -IClasse_Vecteur
CFLAGS = -c -Wall 



all: testMatrice

testMatrice : Matrice.o testMatrice.o
testMatrice.o: testMatrice.cc Matrice.h
Matrice.o: Matrice.cc Matrice.h