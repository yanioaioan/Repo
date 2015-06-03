#-------------------------------------------------
#
# Project created by QtCreator 2015-06-02T11:58:31
#
#-------------------------------------------------

QT       += core

QT       -= gui opengl core

TARGET = VaoTriangle
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    GameModels.cpp \
    display.cpp \
    shader.cpp


OTHER_FILES+= $$PWD/shaders/* \
    shaders/shader.fs

LIBS += -L/usr/local/lib -lSDL2 -L/path/to/glew/lib -lGLEW
LIBS +=  -lGLU -lGL

HEADERS += \
    Vertexformat.h \
    GameModels.h \
    display.h \
    shader.h
