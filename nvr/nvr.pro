#-------------------------------------------------
#
# Project created by QtCreator 2015-06-10T15:58:13
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nvr
TEMPLATE = app


SOURCES += main.cpp \
    src/stream_dev.cpp \
    src/main_menu.cpp \
    src/display_window.cpp \
    src/player_box.cpp \
    src/channel_manager.cpp \
    src/device_discovery.cpp \
    src/yst_usedef.cpp \
    src/transform_encode.cpp

HEADERS  += \
    src/stream_dev.h \
    src/main_menu.h \
    src/display_window.h \
    src/player_box.h \
    common.h \
    error_code.h \
    src/channel_manager.h \
    src/device_discovery.h \
    src/yst_usedef.h \
    src/transform_encode.h

FORMS    += \
    src/main_menu.ui \
    src/channel_manager.ui

include (util/log4qt/log4qt.pri)

TRANSLATIONS += chinese.ts english.ts

RESOURCES += \
    resource.qrc

win32: LIBS += -L$$PWD/lib/win/ -lJvClient

INCLUDEPATH += $$PWD/lib/win
DEPENDPATH += $$PWD/lib/win
