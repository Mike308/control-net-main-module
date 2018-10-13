QT += core
QT -= gui
QT += sql

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
    model/airpressure.cpp \
    dao/controlnetdb.cpp \
    nrfnetwork/3rdparty/utility/RPi/interrupt.cpp \
    nrfnetwork/3rdparty/utility/RPi/spi.cpp \
    nrfnetwork/3rdparty/RF24.cpp \
    nrfnetwork/qnrf24l01.cpp \
    nrfnetwork/qnrf24l01network.cpp \
    nrfnetwork/3rdparty/utility/RPi/bcm2835.c \
    node/nodebus.cpp \
    supervisor.cpp

HEADERS += \
    model/command.h \
    model/temperature.h \
    model/sensor.h \
    model/module.h \
    model/humidity.h \
    model/airpressure.h \
    dao/controlnetdb.h \
    dao/config.h \
    nrfnetwork/3rdparty/utility/RPi/bcm2835.h \
    nrfnetwork/3rdparty/utility/RPi/includes.h \
    nrfnetwork/3rdparty/utility/RPi/interrupt.h \
    nrfnetwork/3rdparty/utility/RPi/RF24_arch_config.h \
    nrfnetwork/3rdparty/utility/RPi/spi.h \
    nrfnetwork/3rdparty/utility/Template/compatibility.h \
    nrfnetwork/3rdparty/utility/Template/gpio.h \
    nrfnetwork/3rdparty/utility/Template/includes.h \
    nrfnetwork/3rdparty/utility/Template/RF24_arch_config.h \
    nrfnetwork/3rdparty/utility/Template/spi.h \
    nrfnetwork/3rdparty/utility/includes.h \
    nrfnetwork/3rdparty/nRF24L01.h \
    nrfnetwork/3rdparty/printf.h \
    nrfnetwork/3rdparty/RF24.h \
    nrfnetwork/3rdparty/RF24_config.h \
    nrfnetwork/qnrf24l01.h \
    nrfnetwork/qnrf24l01network.h \
    node/nodebus.h \
    supervisor.h


target.path = /home/pi/
INSTALLS += target
