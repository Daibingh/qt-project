TEMPLATE=app
TARGET=resize_img
CONFIG -= qt

INCLUDEPATH += /home/daibingh/Programs/opencv331/include \
/home/daibingh/Programs/opencv331/include/opencv \
/home/daibingh/Programs/opencv331/include/opencv2

LIBS += `pkg-config --libs opencv`

SOURCES += \
    main.cpp

