QT *= core\
    serialport

QT -= gui

CONFIG += c++17

TARGET = serialport

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

MY_BUILD_DIR = $$PWD/bin
DESTDIR = $$MY_BUILD_DIR

INCLUDEPATH *= \
    $$PWD \
    $$PWD/src

DEPENDPATH *=  \
    $$PWD/src

HEADERS *= \
    $$PWD/src/softwareserial_9bit.h \
    $$PWD/src/hardwareserial_9bit.h \
    $$PWD/src/serialbase_9bit.h

SOURCES *= \
    $$PWD/src/main.cpp \
    $$PWD/src/softwareserial_9bit.cpp \
    $$PWD/src/hardwareserial_9bit.cpp \
    $$PWD/src/serialbase_9bit.cpp



