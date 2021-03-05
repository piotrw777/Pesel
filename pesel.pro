TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -pthread -pedantic-errors  -O2
SOURCES += \
        date.cpp \
        main.cpp \
        person.cpp

HEADERS += \
    date.h \
    person.h \
    pom_functions.h
