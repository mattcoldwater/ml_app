/********************************************************************************
** Form generated from reading UI file 'log_vis.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOG_VIS_H
#define UI_LOG_VIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_log_vis
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *log_vis)
    {
        if (log_vis->objectName().isEmpty())
            log_vis->setObjectName(QStringLiteral("log_vis"));
        log_vis->resize(800, 600);
        menubar = new QMenuBar(log_vis);
        menubar->setObjectName(QStringLiteral("menubar"));
        log_vis->setMenuBar(menubar);
        centralwidget = new QWidget(log_vis);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        log_vis->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(log_vis);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        log_vis->setStatusBar(statusbar);

        retranslateUi(log_vis);

        QMetaObject::connectSlotsByName(log_vis);
    } // setupUi

    void retranslateUi(QMainWindow *log_vis)
    {
        log_vis->setWindowTitle(QApplication::translate("log_vis", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class log_vis: public Ui_log_vis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOG_VIS_H
