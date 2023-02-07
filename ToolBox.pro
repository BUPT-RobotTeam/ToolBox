 #-------------------------------------------------
#
# Project created by QtCreator 2016-08-12T21:55:19
#
#-------------------------------------------------

# Version
VT_VERSION = 1.04
VT_INTRO_VERSION = 1

# Ubuntu 18.04 (should work on raspbian buster too)
# sudo apt install qml-module-qt-labs-folderlistmodel qml-module-qtquick-extras qml-module-qtquick-controls2 qt5-default libqt5quickcontrols2-5 qtquickcontrols2-5-dev qtcreator qtcreator-doc libqt5serialport5-dev build-essential qml-module-qt3d qt3d5-dev qtdeclarative5-dev

DEFINES += VT_VERSION=$$VT_VERSION
DEFINES += VT_INTRO_VERSION=$$VT_INTRO_VERSION

CONFIG += c++11

#TRANLATION
TRANSLATIONS += res/language/lang_English.ts \
                res/language/lang_Chinese.ts

RC_ICONS = toolbox.ico

# If BLE disconnects on ubuntu after about 90 seconds the reason is most likely that the connection interval is incompatible. This can be fixed with:
# sudo bash -c 'echo 6 > /sys/kernel/debug/bluetooth/hci0/conn_min_interval'

# Bluetooth available
#DEFINES += HAS_BLUETOOTH

# Debug build (e.g. F5 to reload QML files)
#DEFINES += DEBUG_BUILD

# Serial port available
DEFINES += HAS_SERIALPORT

RESOURCES += res.qrc



# V-rep lib
#此处外部库的添加使用了绝对路径，相对路径有问题
#LIBS += -L'D:\\vrepdll' -lremoteApi
#INCLUDEPATH += './v-rep/remoteApi/common'
#DEPENDPATH += './v-rep/remoteApi/common'

#INCLUDEPATH += './v-rep/remoteApi/include'
#DEPENDPATH += './v-rep/remoteApi/include'

#INCLUDEPATH += './v-rep/remoteApi/remoteApi'
#DEPENDPATH += './v-rep/remoteApi/remoteApi'

#DEFINES += NON_MATLAB_PARSING
#DEFINES += MAX_EXT_API_CONNECTIONS=255
#V-rep lib end

QT       += core gui
QT       += widgets
QT       += printsupport
QT       += network
QT       += quick
QT       += quickcontrols2
QT       += charts
QT       += gui

contains(DEFINES, HAS_SERIALPORT) {
    QT       += serialport
}

contains(DEFINES, HAS_BLUETOOTH) {
    QT       += bluetooth
}

TARGET = tool_box_$$VT_VERSION

TEMPLATE = app

release_win {
    DESTDIR = build/win
    OBJECTS_DIR = build/win/obj
    MOC_DIR = build/win/obj
    RCC_DIR = build/win/obj
    UI_DIR = build/win/obj
}

release_lin {
    # http://micro.nicholaswilson.me.uk/post/31855915892/rules-of-static-linking-libstdc-libc-libgcc
    # http://insanecoding.blogspot.se/2012/07/creating-portable-linux-binaries.html
    QMAKE_LFLAGS += -static-libstdc++ -static-libgcc
    DESTDIR = build/lin
    OBJECTS_DIR = build/lin/obj
    MOC_DIR = build/lin/obj
    RCC_DIR = build/lin/obj
    UI_DIR = build/lin/obj
}

release_macos {
    # brew install qt
    DESTDIR = build/macos
    OBJECTS_DIR = build/macos/obj
    MOC_DIR = build/macos/obj
    RCC_DIR = build/macos/obj
    UI_DIR = build/macos/obj
}

SOURCES += main.cpp\
        mainwindow.cpp \
    packet.cpp \
    vbytearray.cpp \
    commands.cpp \
    vescinterface.cpp \
    digitalfiltering.cpp \
    utility.cpp \
    tcpserversimple.cpp \
    bezier.cpp \
    bezier_label.cpp

HEADERS  += mainwindow.h \
    packet.h \
    vbytearray.h \
    commands.h \
    datatypes.h \
    vescinterface.h \
    digitalfiltering.h \
    utility.h \
    tcpserversimple.h \
    bezier.h \
    bezier_label.h

FORMS    += mainwindow.ui

contains(DEFINES, HAS_BLUETOOTH) {
    SOURCES += bleuart.cpp
    HEADERS += bleuart.h
}

include(pages/pages.pri)
include(widgets/widgets.pri)



build_original {
    RESOURCES +=
    DEFINES += VER_ORIGINAL
}
CONFIG += console
