QT += core
QT -= gui

TARGET = FireParameterModel
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    landscape.cpp \
    parameters.cpp \
    climate.cpp

HEADERS += \
    landscape.h \
    parameters.h \
    climate.h

