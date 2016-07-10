#-------------------------------------------------
#
# Project created by QtCreator 2016-07-05T19:44:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DemViewer
TEMPLATE = app


SOURCES += main.cpp\
    View/graphics.cpp \
    Controller/actionlistener.cpp \
    View/graphicscomposite.cpp \
    View/menu.cpp \
    Controller/defaultcontroller.cpp \
    Controller/modulecontroller.cpp \
    Modules/Files/filemodule.cpp \
    Modules/Files/filegraphics.cpp \
    Modules/Files/filecontroller.cpp

HEADERS  += \
    Controller/defaultcontroller.h \
    Controller/actionlistener.h \
    Controller/actioninterface.h \
    Model/deminterface.h \
    Controller/modulecontroller.h \
    View/graphics.h \
    Modules/moduleinterface.h \
    View/graphicscomposite.h \
    View/menu.h \
    Modules/Files/filemodule.h \
    Modules/Files/filegraphics.h \
    Modules/Files/filecontroller.h

FORMS    += widget.ui
