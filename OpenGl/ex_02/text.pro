CONFIG += c++11

TARGET = ex_02_text

INCLUDEPATH = ../general

SOURCES += \
    main_text.cc \
    text_viewer.cc

HEADERS += \
    ../general/contenu.h \
    text_viewer.h \
    ../general/dessinable.h \
    ../general/support_a_dessin.h
