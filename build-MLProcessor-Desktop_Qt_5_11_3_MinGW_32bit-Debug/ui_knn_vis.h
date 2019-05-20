/********************************************************************************
** Form generated from reading UI file 'knn_vis.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KNN_VIS_H
#define UI_KNN_VIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_knn_vis
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *knn_vis)
    {
        if (knn_vis->objectName().isEmpty())
            knn_vis->setObjectName(QStringLiteral("knn_vis"));
        knn_vis->resize(800, 600);
        menubar = new QMenuBar(knn_vis);
        menubar->setObjectName(QStringLiteral("menubar"));
        knn_vis->setMenuBar(menubar);
        centralwidget = new QWidget(knn_vis);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        knn_vis->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(knn_vis);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        knn_vis->setStatusBar(statusbar);

        retranslateUi(knn_vis);

        QMetaObject::connectSlotsByName(knn_vis);
    } // setupUi

    void retranslateUi(QMainWindow *knn_vis)
    {
        knn_vis->setWindowTitle(QApplication::translate("knn_vis", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class knn_vis: public Ui_knn_vis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KNN_VIS_H
