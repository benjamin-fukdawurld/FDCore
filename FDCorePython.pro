#-------------------------------------------------
#
# Project created by QtCreator 2019-07-11T10:28:10
#
#-------------------------------------------------

TARGET = FDCorePython
TEMPLATE = lib
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += link_pkgconfig
PKGCONFIG += python3

DESTDIR = ../build/lib
MAKEFILE = ../build/makefiles/$${TARGET}
OBJECTS_DIR = ../build/obj/$${TARGET}

LIBS += -L../build/lib -lFDCore \
    -L../thirdparty/assimp/bin \
    -lassimp

INCLUDEPATH += include \
    ../FDCore/include \
    ../thirdparty/pybind11/include \

SOURCES += \
    src/ThreadPool_python.cpp \
    src/TimeManager_python.cpp \
    src/Resource_python.cpp \
    src/Object_python.cpp

HEADERS += \
    include/FDCore/Binding/Python/FDCorePython.h \
    include/FDCore/Binding/Python/ThreadPool_python.h \
    include/FDCore/Binding/Python/TimeManager_python.h \
    include/FDCore/Binding/Python/Resource_python.h \
    include/FDCore/Binding/Python/Object_python.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
