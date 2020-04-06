CXX = g++
CXXFLAGS = -Wall -std=c++11 -pedantic -Wall
SRC =  $(EXEC).cc ../../Classe_Integrateur/Integrateur.cc ../../Classe_Integrable/Integrable.cc ../../Classe_Integrable/Classe_Toupie/Toupie.cc  \
../../Classe_Vecteur/Vecteur.cc text/text_viewer.cc ../../Classe_Systeme/Systeme.cc ../../Classe_Matrice/Matrice.cc ../../constantes.cc


OBJ = $(SRC:.cc=.o)
EXEC = exerciceP9b

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LBLIBS)

