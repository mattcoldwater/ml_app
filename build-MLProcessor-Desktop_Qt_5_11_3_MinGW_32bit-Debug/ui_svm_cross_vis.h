/********************************************************************************
** Form generated from reading UI file 'svm_cross_vis.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVM_CROSS_VIS_H
#define UI_SVM_CROSS_VIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_svm_cross_vis
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *svm_cross_vis)
    {
        if (svm_cross_vis->objectName().isEmpty())
            svm_cross_vis->setObjectName(QStringLiteral("svm_cross_vis"));
        svm_cross_vis->resize(800, 600);
        menubar = new QMenuBar(svm_cross_vis);
        menubar->setObjectName(QStringLiteral("menubar"));
        svm_cross_vis->setMenuBar(menubar);
        centralwidget = new QWidget(svm_cross_vis);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        svm_cross_vis->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(svm_cross_vis);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        svm_cross_vis->setStatusBar(statusbar);

        retranslateUi(svm_cross_vis);

        QMetaObject::connectSlotsByName(svm_cross_vis);
    } // setupUi

    void retranslateUi(QMainWindow *svm_cross_vis)
    {
        svm_cross_vis->setWindowTitle(QApplication::translate("svm_cross_vis", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class svm_cross_vis: public Ui_svm_cross_vis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVM_CROSS_VIS_H
