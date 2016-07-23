#-------------------------------------------------
#
# Project created by QtCreator 2016-06-27T00:51:57
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dem
TEMPLATE = app


SOURCES += main.cpp\
        demproject.cpp \
    helper.cpp \
    glwidget.cpp \
    meshing.cpp \
    scrollviewport.cpp

HEADERS  += demproject.h \
    helper.h \
    glwidget.h \
    meshing.h \
    scrollviewport.h

FORMS    += demproject.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../../usr/local/Cellar/gdal/1.11.3_1/lib/release/ -lgdal
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../../usr/local/Cellar/gdal/1.11.3_1/lib/debug/ -lgdal
else:unix: LIBS += -L$$PWD/../../../../../../../../usr/local/Cellar/gdal/1.11.3_1/lib/ -lgdal

INCLUDEPATH += $$PWD/../../../../../../../../usr/local/Cellar/gdal/1.11.3_1/include
DEPENDPATH += $$PWD/../../../../../../../../usr/local/Cellar/gdal/1.11.3_1/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../../usr/local/Cellar/gdal/1.11.3_1/lib/release/libgdal.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../../usr/local/Cellar/gdal/1.11.3_1/lib/debug/libgdal.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../../usr/local/Cellar/gdal/1.11.3_1/lib/release/gdal.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../../usr/local/Cellar/gdal/1.11.3_1/lib/debug/gdal.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../../../../../usr/local/Cellar/gdal/1.11.3_1/lib/libgdal.a
