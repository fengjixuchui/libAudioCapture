TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

SOURCES += \
        main.cpp

INCLUDEPATH += ../
LIBS += -L.. -lAudioCapture
