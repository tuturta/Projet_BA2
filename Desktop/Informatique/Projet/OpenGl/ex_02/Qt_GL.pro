QT += core gui opengl widgets
CONFIG += c++11

win32:LIBS += -lopengl32

TARGET = ex_02_gl

INCLUDEPATH = ../general

SOURCES += \
    main_qt_gl.cc \
    glwidget.cc \
    vue_opengl.cc

HEADERS += \
    glwidget.h \
    vertex_shader.h \
    vue_opengl.h \
    ../general/dessinable.h \
    ../general/support_a_dessin.h \
    ../general/contenu.h

RESOURCES += \
    resource.qrc
