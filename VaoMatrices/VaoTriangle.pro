#-------------------------------------------------
#
# Project created by QtCreator 2015-06-02T11:58:31
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = VaoTriangle
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += src/main.cpp \
    src/display.cpp \
    src/shader.cpp \
    src/singleton.cpp \
    src/ModelLoader.cpp


HEADERS += \
    include/Vertexformat.h \
    include/display.h \
    include/shader.h \
    include/singleton.h \
    include/ModelLoader.h

INCLUDEPATH +=$$PWD/include
MOC_DIR=moc

OTHER_FILES+= $$PWD/shaders/*

OBJECTS_DIR=obj

LIBS += -L/usr/local/lib -lSDL2 -L/path/to/glew/lib -lGLEW
LIBS +=  -lGLU -lGL
