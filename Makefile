CXX = g++
CC = $(CXX)
CXXFLAGS = -g -std=c++11 -Wall -IClasse_Vecteur


all: testVecteur

testVecteur : Vecteur.o testVecteur.o
testVecteur.o: testVecteur.cc Vecteur.h
Vecteur.o: Vecteur.cc Vecteur.h