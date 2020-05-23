CONFIG += c++11

TARGET = exerciceP9

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
     text_viewer.cc \
     exerciceP9b.cc \
   # exerciceP11.cc \
   # exerciceP12.cc

HEADERS += \
    text_viewer.h \
    ../general/dessinable.h \
    ../general/support_a_dessin.h \
    ../general/Classe_Integrable/Classe_Toupie/Toupie.h \
    ../general/Classe_Systeme/Systeme.h \
    ../general/Classe_Integrable/Integrable.h \
    ../general/Classe_Integrateur/Integrateur.h \

