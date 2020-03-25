CXX = g++
CXXFLAGS = -Wall -std=c++17 -g -fsanitize=address
LDFLAGS =  -fsanitize=address

SRC = Integrateur.cc testIntegrateur.cc ../Classe_Toupie/Toupie.cc ../Classe_Vecteur/Vecteur.cc
OBJ = $(SRC:.cc=.o)
EXEC = testIntegrateur

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

