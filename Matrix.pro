QT += core
QT -= gui

CONFIG += c++11

TARGET = Matrix
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    tmatrix.cpp

HEADERS += \
    tmatrix.h
