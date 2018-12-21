TEMPLATE = app
CONFIG += console c++11
CONFIG -= qt
CONFIG += app_bundle

INCLUDEPATH += /home/daibingh/Programs/opencv331/include \
                /home/daibingh/Programs/opencv331/include/opencv \
                /home/daibingh/Programs/opencv331/include/opencv2

LIBS += /home/daibingh/Programs/opencv331/lib/lib*

SOURCES += \
    main.cpp
