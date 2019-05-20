/********************************************************************************
** Form generated from reading UI file 'svm.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVM_H
#define UI_SVM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_svm
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *widget;
    QMenuBar *menubar;
    QMenu *menuSVM;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *svm)
    {
        if (svm->objectName().isEmpty())
            svm->setObjectName(QStringLiteral("svm"));
        svm->resize(800, 600);
        centralwidget = new QWidget(svm);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        svm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(svm);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menuSVM = new QMenu(menubar);
        menuSVM->setObjectName(QStringLiteral("menuSVM"));
        svm->setMenuBar(menubar);
        statusbar = new QStatusBar(svm);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        svm->setStatusBar(statusbar);

        menubar->addAction(menuSVM->menuAction());

        retranslateUi(svm);

        QMetaObject::connectSlotsByName(svm);
    } // setupUi

    void retranslateUi(QMainWindow *svm)
    {
        svm->setWindowTitle(QApplication::translate("svm", "MainWindow", nullptr));
        menuSVM->setTitle(QApplication::translate("svm", "SVM", nullptr));
    } // retranslateUi

};

namespace Ui {
    class svm: public Ui_svm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVM_H
