CONFIG += c++11

TARGET = exerciceP9b

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    exerciceP9b.cc \
    text_viewer.cc

HEADERS += \
    text_viewer.h \
    ../general/dessinable.h \
    ../general/support_a_dessin.h \
    ../general/Classe_Integrable/Classe_Toupie/Toupie.h \
    ../general/Classe_Systeme/Systeme.h \
    ../general/Classe_Integrable/Integrable.h