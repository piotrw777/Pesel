TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -pthread -pedantic-errors  -O2 -std=c++17
SOURCES += \
        date.cpp \
        main.cpp \
        person.cpp

HEADERS += \
    date.h \
    person.h \
    pom_functions.h
