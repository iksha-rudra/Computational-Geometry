TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11

SOURCES += main.cpp \
    DataStructures/point.cpp \
    DataStructures/minheap.cpp \
    CGAlgorithms/cgalgorithms.cpp \
    DataStructures/linkedstack.cpp

HEADERS += \
    DataStructures/point.h \
    DataStructures/minheap.h \
    CGAlgorithms/cgalgorithms.h \
    DataStructures/linkedstack.h


