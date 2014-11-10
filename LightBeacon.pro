APP_NAME = LightBeacon

QMAKE_CXXFLAGS += -Wc,-std=c++0x -Wc,-pedantic

CONFIG += qt warn_on cascades10 C++11
LIBS += -lcamapi

include(config.pri)
