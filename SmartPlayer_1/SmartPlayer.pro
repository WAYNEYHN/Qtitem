#-------------------------------------------------
#
# Project created by QtCreator 2020-07-13T10:54:43
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartPlayer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        widget.cpp \
    audio.cpp \
    gettoken.cpp \
    speech2text.cpp \
    text2speech.cpp \
    robot.cpp

HEADERS  += widget.h \
    audio.h \
    gettoken.h \
    speech2text.h \
    text2speech.h \
    robot.h

FORMS    += widget.ui

RESOURCES += \
    resource.qrc

DISTFILES += \
    dong.wav
