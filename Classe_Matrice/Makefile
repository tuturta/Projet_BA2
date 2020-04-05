#CXX = g++
#CXXFLAGS = -Wall -std=c++17 -g
#ADRESS =  ../Classe_Vecteur/

#all: testMatrice

#testMatrice : Matrice.o testMatrice.o ../Classe_Vecteur/Vecteur.o

#Matrice.o: Matrice.cc ../Classe_Vecteur/Vecteur.h Matrice.h 
#testMatrice.o: testMatrice.cc Matrice.h ../Classe_Vecteur/Vecteur.h 
#../Classe_Vecteur/Vecteur.o : $(ADRESS)Vecteur.cc $(ADRESS)Vecteur.h

CXX = g++
CXXFLAGS = -Wall -std=c++11 -pedantic -Wall
SRC = testMatrice.cc Matrice.cc ../Classe_Vecteur/Vecteur.cc


OBJ = $(SRC:.cc=.o)
EXEC = testMatrice

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LBLIBS)

