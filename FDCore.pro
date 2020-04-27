TARGET = FDCore
TEMPLATE = lib
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../build/lib
MAKEFILE = ../build/makefiles/$${TARGET}
OBJECTS_DIR = ../build/obj/$${TARGET}

INCLUDEPATH += \
    include \

SOURCES += \
    src/FileUtils.cpp \
    src/ThreadPool.cpp

HEADERS += \
    include/FDCore/AssociativeContainer.h \
    include/FDCore/CRTPTrait.h \
    include/FDCore/ComparableTrait.h \
    include/FDCore/EnumFlag.h \
    include/FDCore/FileUtils.h \
    include/FDCore/Identifiable.h \
    include/FDCore/NonCopyableTrait.h \
    include/FDCore/TimeManager.h \
    include/FDCore/TypeInformation.h \
    include/FDCore/Singleton.h \
    include/FDCore/CopyOnWrite.h \
    include/FDCore/CallOnEdit.h \
    include/FDCore/ThreadPool.h \
    include/FDCore/Macros.h \

unix {
    target.path = /usr/lib
    INSTALLS += target
}
