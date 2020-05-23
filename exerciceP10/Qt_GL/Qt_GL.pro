QT += core gui opengl widgets
CONFIG += c++11

win32:LIBS += -lopengl32


TARGET = exerciceP10

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    exerciceP10.cc \
    glwidget.cc \
    vue_opengl.cc \
    glcone.cc \
    glsphere_tronquee.cc \

HEADERS += \
    glwidget.h \
    vertex_shader.h \
    vue_opengl.h \
    glcone.h \
    glsphere_tronquee.h \
    ../general/dessinable.h \
    ../general/support_a_dessin.h \   
    ../general/Classe_Integrable/Integrable.h \
    ../general/Classe_Integrable/Classe_Toupie/Toupie.h \
    ../general/Classe_Integrateur/Integrateur.h \
    ../general/Classe_Vecteur/Vecteur.h \
    ../general/dessinable.h \ #VRAIMENT BESOIN ? -> VERIFIER
    ../general/Classe_Systeme/Syteme.h \
    ../general/constante.h \



RESOURCES += \
    resource.qrc
