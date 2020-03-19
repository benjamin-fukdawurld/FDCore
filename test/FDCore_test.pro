#-------------------------------------------------
#
# Project created by FDProjectUtils on 11/24/2019, 16:41:33
#
#-------------------------------------------------

TARGET = FDCore_test
TEMPLATE = app
CONFIG += console c++17 
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../build/bin
MAKEFILE = ../build/makefiles/$${TARGET}
OBJECTS_DIR = ../build/.obj/$${TARGET}

LIBS += \
    -L../../build/lib \
    -L../../thirdparty/googletest/build/lib \

LIBS += \
    -pthread \
    -lgtest \
    -lFDCore \

INCLUDEPATH += \
    include \
    ../../thirdparty/googletest/googletest/include \

SOURCES += \
    main.cpp

HEADERS += \
    FileUtils_test.h
