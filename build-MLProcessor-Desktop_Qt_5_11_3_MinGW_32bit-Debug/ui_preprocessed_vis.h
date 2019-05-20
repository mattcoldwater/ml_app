/********************************************************************************
** Form generated from reading UI file 'preprocessed_vis.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREPROCESSED_VIS_H
#define UI_PREPROCESSED_VIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_preprocessed_vis
{
public:
    QWidget *centralwidget;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QWidget *widget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *preprocessed_vis)
    {
        if (preprocessed_vis->objectName().isEmpty())
            preprocessed_vis->setObjectName(QStringLiteral("preprocessed_vis"));
        preprocessed_vis->resize(1056, 794);
        centralwidget = new QWidget(preprocessed_vis);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(0, 0, 91, 22));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(100, 0, 75, 23));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 30, 1031, 701));
        preprocessed_vis->setCentralWidget(centralwidget);
        menubar = new QMenuBar(preprocessed_vis);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1056, 23));
        preprocessed_vis->setMenuBar(menubar);
        statusbar = new QStatusBar(preprocessed_vis);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        preprocessed_vis->setStatusBar(statusbar);

        retranslateUi(preprocessed_vis);

        QMetaObject::connectSlotsByName(preprocessed_vis);
    } // setupUi

    void retranslateUi(QMainWindow *preprocessed_vis)
    {
        preprocessed_vis->setWindowTitle(QApplication::translate("preprocessed_vis", "MainWindow", nullptr));
        comboBox->setItemText(0, QApplication::translate("preprocessed_vis", "Direction1", nullptr));
        comboBox->setItemText(1, QApplication::translate("preprocessed_vis", "Direction2", nullptr));
        comboBox->setItemText(2, QApplication::translate("preprocessed_vis", "Direction3", nullptr));

        pushButton->setText(QApplication::translate("preprocessed_vis", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class preprocessed_vis: public Ui_preprocessed_vis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREPROCESSED_VIS_H
