TEMPLATE = lib

CONFIG = staticlib c++11

SOURCES = erreurs.cc constantes.cc Classe_Integrable/Integrable.cc Classe_Integrable/Classe_Toupie/Toupie.cc Classe_Integrateur/Integrateur.cc Classe_Matrice/Matrice.cc Classe_Systeme/Systeme.cc Classe_Vecteur/Vecteur.cc 

HEADERS += \
    dessinable.h \
    support_a_dessin.h \
    erreurs.h \
    constantes.h \
    Classe_Integrable/Integrable.cc \
    Classe_Integrable/Classe_Toupie/Toupie.cc \
    Classe_Integrateur/Integrateur.cc \
    Classe_Matrice/Matrice.cc \
    Classe_Systeme/Systeme.cc \
    Classe_Vecteur/Vecteur.cc \
