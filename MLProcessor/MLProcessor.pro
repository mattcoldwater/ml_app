#-------------------------------------------------
# Haoyu Wu
# Project created by QtCreator 2019-04-16T14:17:44
#
#-------------------------------------------------

QT       += core gui datavisualization charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MLProcessor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

target.path = $$[QT_INSTALL_EXAMPLES]/datavisualization/$$TARGET
INSTALLS += target

FORMS += \
    extract_vis.ui \
    knn_vis.ui \
    dialog.ui \
    svm.ui \
    preprocessed_vis.ui \
    svm_cross_vis.ui \
    log_vis.ui \
    log_cross_vis.ui \
    model_evaluation_visualization.ui

HEADERS += \
    utils_why.h \
    svm.h \
    extract_vis.h \
    mlprocess.h \
    feature_for_vis.h \
    pca.h \
    cluster.h \
    crossvalidation.h \
    knn_vis.h \
    knn.h \
    kmean_pca.h \
    CDTree.hpp \
    tree_vis.h \
    preprocessed_vis.h \
    naivebayes.h \
    dialog.h \
    getfeatures.h \
    importPeptide.h \
    RFCSV.hpp \
    getfeaturename.h \
    showwidget.h \
    redundancy.h \
    svm_cross_vis.h \
    sigmoid.h \
    optimization.h \
    predict.h \
    doublearray.h \
    segmentation.h \
    quick_sort_cksaap.h \
    log_vis.h \
    log_cross_vis.h \
    model_evaluation.h \
    model_evaluation_visualization.h

SOURCES += \
    mlprocess.cpp \
    utils_why.cpp \
    svm.cpp \
    preprocessed_vis.cpp \
    extract_vis.cpp \
    feature_for_vis.cpp \
    knn_vis.cpp \
    naivebayes.cpp \
    crossvalidation.cpp \
    showwidget.cpp \
    knn.cpp \
    importPeptide.cpp \
    CDTree.cpp \
    main.cpp \
    test_main.cpp \
    DecisionTree.cpp \
    tree_vis.cpp \
    dialog.cpp \
    main_zmj.cpp \
    pca.cpp \
    getfeatures.cpp \
    getfeaturename.cpp \
    svm_cross_vis.cpp \
    doublearray.cpp \
    sigmoid.cpp \
    optimization.cpp \
    predict.cpp \
    segmentation.cpp \
    quick_sort_cksaap.cpp \
    log_vis.cpp \
    log_cross_vis.cpp \
    model_evaluation.cpp \
    model_evaluation_visualization.cpp

