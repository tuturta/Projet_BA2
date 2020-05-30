
CXX = g++
CXXFLAGS = -Wall -std=c++11 -pedantic -Wall

NB_EXO = 9b
SRC = exerciceP$(NB_EXO).cc text_viewer.cc \
	../general/Classe_Integrable/Classe_Toupie/Toupie.cc \
	../general/Classe_Integrateur/Integrateur.cc \
	../general/erreurs.cc \
	../general/Classe_Systeme/Systeme.cc \
	../general/Classe_Integrable/Integrable.cc \
	../general/Classe_Matrice/Matrice.cc \
	../general/Classe_Vecteur/Vecteur.cc \
	../general/constantes.cc \


OBJ = $(SRC:.cc=.o)
EXEC = exerciceP$(NB_EXO)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LBLIBS)