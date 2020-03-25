CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

SRC = Integrateur.cc testIntegrateur.cc ../Classe_Toupie/Toupie.cc ../Classe_Vecteur/Vecteur.cc
OBJ = $(SRC:.cc=.o)
EXEC = testIntegrateur

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LBLIBS)

