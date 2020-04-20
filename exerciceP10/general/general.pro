TEMPLATE = lib

CONFIG = staticlib c++11

SOURCES = Classe_Vecteur/Vecteur.cc Classe_Matrice/Matrice.cc erreurs.cc constantes.cc Classe_Integrable/Integrable.cc Classe_Integrable/Classe_Toupie/Toupie.cc Classe_Integrateur/Integrateur.cc #Classe_Systeme/Systeme.cc

HEADERS += \
    Classe_Vecteur/Vecteur.h \
    Classe_Matrice/Matrice.h \
    dessinable.h \
    support_a_dessin.h \
    erreurs.h \
    constantes.h \
    Classe_Integrable/Integrable.h \
    Classe_Integrable/Classe_Toupie/Toupie.h \
    Classe_Integrateur/Integrateur.h \
    #Classe_Systeme/Systeme.h \

