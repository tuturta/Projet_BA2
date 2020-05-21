CXX = g++
CXXFLAGS = -Wall -std=c++11 -pedantic -Wall
SRC =  testIntegrateur.cc Integrateur.cc ../Classe_Integrable/Integrable.cc ../Classe_Integrable/Classe_Toupie/Toupie.cc ../Classe_Vecteur/Vecteur.cc ../Open_GL/Classe_Dessinable/text/text_viewer.cc ../Classe_Systeme/Systeme.cc ../constantes.cc ../Classe_Matrice/Matrice.cc ../erreurs.cc


OBJ = $(SRC:.cc=.o)
EXEC = testIntegrateur

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LBLIBS)


#all : testIntegrateur

#testIntegrateur : Integrateur.o testIntegrateur.o 
#Integrateur.o : Integrateur.cc Integrateur.h
#testIntegrateur.o : testIntegrateur.cc Integrateur.h ../Open_GL/Classe_Dessinable/text/text_viewer.h
#text_viewer.o : ../Open_GL/Classe_Dessinable/text/text_viewer.cc ../Open_GL/Classe_Dessinable/text/text_viewer.h