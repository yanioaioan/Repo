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
    src/ModelLoader.cpp \
    objloaderlib/objTester/objTester/list.cpp \
    objloaderlib/objTester/objTester/objLoader.cpp \
    objloaderlib/objTester/objTester/obj_parser.cpp \
    objloaderlib/objTester/objTester/objTester.cpp \
    objloaderlib/objTester/objTester/string_extra.cpp

HEADERS += \
    include/display.h \
    include/shader.h \
    include/singleton.h \
    include/ModelLoader.h \
    include/VertexStructure.h \
    objloaderlib/objTester/objTester/list.h \
    objloaderlib/objTester/objTester/objLoader.h \
    objloaderlib/objTester/objTester/obj_parser.h \
    objloaderlib/objTester/objTester/string_extra.h

INCLUDEPATH +=$$PWD/include
MOC_DIR=moc

OTHER_FILES+= $$PWD/shaders/*

OBJECTS_DIR=obj

LIBS += -L/usr/local/lib -lSDL2 -L/path/to/glew/lib -lGLEW
LIBS +=  -lGLU -lGL


LIBS += -L/$(HOME)/NGL/lib -l NGL
INCLUDEPATH += $$(HOME)/NGL/include/
INCLUDEPATH +=$$PWD/objloaderlib/objTester/objTester/
