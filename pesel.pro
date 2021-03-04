TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -pthread -pedantic-errors  -O2
SOURCES += \
        main.cpp
