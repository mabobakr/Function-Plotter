QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_calculatortesting.cpp \
    calculator.cpp

HEADERS += \
    calculator.h
