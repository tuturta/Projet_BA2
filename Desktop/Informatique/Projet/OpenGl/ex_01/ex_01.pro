#
# Ce fichier est lu par le programme qmake pour générer le Makefile
#

QT += core gui opengl widgets
CONFIG += c++11

win32:LIBS += -lopengl32


TARGET   = ex_01
TEMPLATE = app

SOURCES += \
    main_qt_gl.cc \
    glwidget.cc

HEADERS += \
    glwidget.h \
    vertex_shader.h

RESOURCES += \
    resource.qrc
