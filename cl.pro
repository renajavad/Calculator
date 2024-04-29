TEMPLATE = app
TARGET = YU
QT = core gui
greaterThan(QT_MAJOR_VERSION, 4):
QT+=widgets
SOURCES += calculate.cpp \
    main.cpp

HEADERS += \
    calculate.h
