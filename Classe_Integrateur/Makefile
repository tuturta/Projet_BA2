CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

#SRC = Integrateur.cc testIntegrateur.cc ../Open_GL/Classe_Dessinable/text/text_viewer.cc 
#OBJ = $(SRC:.cc=.o)
#EXEC = testIntegrateur

#all: $(EXEC)

#$(EXEC): $(OBJ)
#	$(CXX) -o $@ $(OBJ) $(LBLIBS)


all : testIntegrateur

testIntegrateur : Integrateur.o testToupie.o ../Open_GL/Classe_Dessinable/text/text_viewer.o
Integrateur.o : Integrateur.cc Integrateur.h
testToupie.o : testIntegrateur.cc Integrateur.h ../Open_GL/Classe_Dessinable/text/text_viewer.h
text_viewer.o : text_viewer.cc text_viewer.h