QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = test_process_image_in_window
TEMPLATE = app

INCLUDEPATH += /home/daibingh/Programs/opencv331/include \
                /home/daibingh/Programs/opencv331/include/opencv \
                /home/daibingh/Programs/opencv331/include/opencv2

LIBS += /home/daibingh/Programs/opencv331/lib/lib*

SOURCES += \
    main.cpp \
    imageprocess.cpp

HEADERS += \
    imageprocess.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc
