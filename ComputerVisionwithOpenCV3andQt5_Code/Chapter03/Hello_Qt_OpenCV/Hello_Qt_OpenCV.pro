#-------------------------------------------------
#
# Project created by QtCreator 2017-08-27T11:21:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hello_Qt_OpenCV
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


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

win32: {
    include(c:/dev/opencv/opencv.pri)
}

#unix: !macx{
#    CONFIG += link_pkgconfig
#    PKGCONFIG += opencv
#}

unix: macx{
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib \
    -lopencv_world
}

RESOURCES += \
    resources.qrc

TRANSLATIONS = translation_de.ts translation_tr.ts


INCLUDEPATH += /home/daibingh/Programs/opencv331/include \
                /home/daibingh/Programs/opencv331/include/opencv \
                /home/daibingh/Programs/opencv331/include/opencv2

LIBS += /home/daibingh/Programs/opencv331/lib/lib*