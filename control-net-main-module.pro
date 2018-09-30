QT += core
QT -= gui

CONFIG += c++11

TARGET = control-net-main-module
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    model/command.cpp \
    model/temperature.cpp \
    model/sensor.cpp \
    model/module.cpp \
    model/humidity.cpp \
    model/airpressure.cpp

HEADERS += \
    model/command.h \
    model/temperature.h \
    model/sensor.h \
    model/module.h \
    model/humidity.h \
    model/airpressure.h
