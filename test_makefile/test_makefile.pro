TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../darknet/examples/art.c \
    ../darknet/examples/attention.c \
    ../darknet/examples/captcha.c \
    ../darknet/examples/cifar.c \
    ../darknet/examples/classifier.c \
    ../darknet/examples/coco.c \
    ../darknet/examples/darknet.c \
    ../darknet/examples/detector.c \
    ../darknet/examples/dice.c \
    ../darknet/examples/go.c \
    ../darknet/examples/instance-segmenter.c \
    ../darknet/examples/lsd.c \
    ../darknet/examples/nightmare.c \
    ../darknet/examples/regressor.c \
    ../darknet/examples/rnn.c \
    ../darknet/examples/rnn_vid.c \
    ../darknet/examples/segmenter.c \
    ../darknet/examples/super.c \
    ../darknet/examples/swag.c \
    ../darknet/examples/tag.c \
    ../darknet/examples/voxel.c \
    ../darknet/examples/writing.c \
    ../darknet/examples/yolo.c \
    ../darknet/src/image_opencv.cpp \
    ../darknet/src/activation_layer.c \
    ../darknet/src/activations.c \
    ../darknet/src/avgpool_layer.c \
    ../darknet/src/batchnorm_layer.c \
    ../darknet/src/blas.c \
    ../darknet/src/box.c \
    ../darknet/src/col2im.c \
    ../darknet/src/compare.c \
    ../darknet/src/connected_layer.c \
    ../darknet/src/convolutional_layer.c \
    ../darknet/src/cost_layer.c \
    ../darknet/src/crnn_layer.c \
    ../darknet/src/crop_layer.c \
    ../darknet/src/cuda.c \
    ../darknet/src/data.c \
    ../darknet/src/deconvolutional_layer.c \
    ../darknet/src/demo.c \
    ../darknet/src/detection_layer.c \
    ../darknet/src/dropout_layer.c \
    ../darknet/src/gemm.c \
    ../darknet/src/gru_layer.c \
    ../darknet/src/im2col.c \
    ../darknet/src/image.c \
    ../darknet/src/iseg_layer.c \
    ../darknet/src/l2norm_layer.c \
    ../darknet/src/layer.c \
    ../darknet/src/list.c \
    ../darknet/src/local_layer.c \
    ../darknet/src/logistic_layer.c \
    ../darknet/src/lstm_layer.c \
    ../darknet/src/matrix.c \
    ../darknet/src/maxpool_layer.c \
    ../darknet/src/network.c \
    ../darknet/src/normalization_layer.c \
    ../darknet/src/option_list.c \
    ../darknet/src/parser.c \
    ../darknet/src/region_layer.c \
    ../darknet/src/reorg_layer.c \
    ../darknet/src/rnn_layer.c \
    ../darknet/src/route_layer.c \
    ../darknet/src/shortcut_layer.c \
    ../darknet/src/softmax_layer.c \
    ../darknet/src/tree.c \
    ../darknet/src/upsample_layer.c \
    ../darknet/src/utils.c \
    ../darknet/src/yolo_layer.c

HEADERS += \
    ../darknet/src/activation_layer.h \
    ../darknet/src/activations.h \
    ../darknet/src/avgpool_layer.h \
    ../darknet/src/batchnorm_layer.h \
    ../darknet/src/blas.h \
    ../darknet/src/box.h \
    ../darknet/src/classifier.h \
    ../darknet/src/col2im.h \
    ../darknet/src/connected_layer.h \
    ../darknet/src/convolutional_layer.h \
    ../darknet/src/cost_layer.h \
    ../darknet/src/crnn_layer.h \
    ../darknet/src/crop_layer.h \
    ../darknet/src/cuda.h \
    ../darknet/src/data.h \
    ../darknet/src/deconvolutional_layer.h \
    ../darknet/src/demo.h \
    ../darknet/src/detection_layer.h \
    ../darknet/src/dropout_layer.h \
    ../darknet/src/gemm.h \
    ../darknet/src/gru_layer.h \
    ../darknet/src/im2col.h \
    ../darknet/src/image.h \
    ../darknet/src/iseg_layer.h \
    ../darknet/src/l2norm_layer.h \
    ../darknet/src/layer.h \
    ../darknet/src/list.h \
    ../darknet/src/local_layer.h \
    ../darknet/src/logistic_layer.h \
    ../darknet/src/lstm_layer.h \
    ../darknet/src/matrix.h \
    ../darknet/src/maxpool_layer.h \
    ../darknet/src/network.h \
    ../darknet/src/normalization_layer.h \
    ../darknet/src/option_list.h \
    ../darknet/src/parser.h \
    ../darknet/src/region_layer.h \
    ../darknet/src/reorg_layer.h \
    ../darknet/src/rnn_layer.h \
    ../darknet/src/route_layer.h \
    ../darknet/src/shortcut_layer.h \
    ../darknet/src/softmax_layer.h \
    ../darknet/src/stb_image.h \
    ../darknet/src/stb_image_write.h \
    ../darknet/src/tree.h \
    ../darknet/src/upsample_layer.h \
    ../darknet/src/utils.h \
    ../darknet/src/yolo_layer.h

INCLUDEPATH += /home/daibingh/qt-pro/darknet/include \
/home/daibingh/qt-pro/darknet/src

LIBS += /home/daibingh/Programs/opencv331/lib/lib*
