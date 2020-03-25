export CXX = g++
export CXXFLAGS = -Wall -std=c++17 -g -fsanitize=address
export LDFLAGS =  -fsanitize=address


#############A MODIFIER################

CLASSNAME = Vecteur

#############PAS TOUCHE##################

#Indique le repertoire ou se trouve le "sous make"
REPERTOIRE = Classe_$(CLASSNAME)

#Indique le nom du fichier que l'on veut creer dans le repertoire REPERTOIRE
EXEC = $(REPERTOIRE)/test$(CLASSNAME)


#Permet d'executer le make au repertoire donné :


all: $(EXEC)

$(EXEC):
	@(cd $(REPERTOIRE) && $(MAKE))
