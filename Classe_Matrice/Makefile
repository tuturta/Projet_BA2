ADRESS =  ../Classe_Vecteur/

all: testMatrice

testMatrice : Matrice.o testMatrice.o $(ADRESS)Vecteur.o

testMatrice.o: testMatrice.cc Matrice.h $(ADRESS)Vecteur.h ../erreurs.h
Matrice.o: testMatrice.cc Matrice.h $(ADRESS)Vecteur.h 
Vecteur.o : $(ADRESS)Vecteur.cc $(ADRESS)Vecteur.h 