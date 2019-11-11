TARGET = FDCore
TEMPLATE = lib
CONFIG += console c++17
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../build/lib
MAKEFILE = ../build/makefiles/$${TARGET}
OBJECTS_DIR = ../build/.obj/$${TARGET}

DEPENDPATH += \
    include \

INCLUDEPATH += \
    include \

SOURCES += \
    src/FileUtils.cpp

HEADERS += \
    include/FDCore/FileUtils.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
