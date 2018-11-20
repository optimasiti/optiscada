#-------------------------------------------------
#
# Project created by QtCreator 2018-10-17T09:30:13
#
#-------------------------------------------------

QT       += core gui serialbus network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OptiScada
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tagscada.cpp \
    scadacore.cpp \
    devicemodbusethernet.cpp \
    modbusmemory.cpp \
    modbuscommon.cpp \
    log.cpp \
    writecommand.cpp \
    scadabuilder.cpp

HEADERS  += mainwindow.h \
    tagscada.h \
    scadacore.h \
    devicemodbusethernet.h \
    modbusmemory.h \
    modbuscommon.h \
    log.h \
    writecommand.h \
    scadabuilder.h

FORMS    += mainwindow.ui
