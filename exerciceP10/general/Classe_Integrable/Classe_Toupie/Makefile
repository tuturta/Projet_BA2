XX = g++
CXXFLAGS = -Wall -std=c++11 -pedantic -Wall

NB_EXO = 9B
SRC = testToupie.cc \
	Toupie.cc \
	../../Classe_Integrateur/Integrateur.cc \
	../../../text/text_viewer.cc \
	../../Classe_Systeme/Systeme.cc \
	../Integrable.cc \
	../../Classe_Matrice/Matrice.cc \
	../../Classe_Vecteur/Vecteur.cc \
	../../constantes.cc \


OBJ = $(SRC:.cc=.o)
EXEC = testToupie

$(EXEC): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LBLIBS)