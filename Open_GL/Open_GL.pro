TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Classe_Dessinable/text/text_viewer.cc \
        main.cpp

HEADERS += \
    Classe_Dessinable/general/contenu.h \
    Classe_Dessinable/general/dessinable.h \
    Classe_Dessinable/general/support_a_dessin.h \
    Classe_Dessinable/text/text_viewer.h
