#-------------------------------------------------
#
# Project created by QtCreator 2019-07-11T10:28:10
#
#-------------------------------------------------

TARGET = FDCoreJson
TEMPLATE = lib
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../build/lib
MAKEFILE = ../build/makefiles/$${TARGET}
OBJECTS_DIR = ../build/obj/$${TARGET}

LIBS += -L../build/lib -lFDCore -lFDSerialize -lFDJson \

INCLUDEPATH += include \
    ../FDSerialize/include \
    ../FDJson/include \
    ../thirdparty/rapidjson/include \

SOURCES +=

HEADERS += \
    include/FDCore/Serialization/Json/FDCoreJson_fwd.h \
    include/FDCore/Serialization/Json/FDCoreJson.h \
    include/FDCore/Serialization/Json/Resource_json.h \
    include/FDCore/Serialization/Json/Resource_json_fwd.h \
    include/FDCore/Serialization/Json/Object_json.h \
    include/FDCore/Serialization/Json/Object_json_fwd.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
