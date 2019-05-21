/********************************************************************************
** Form generated from reading UI file 'extract_vis.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTRACT_VIS_H
#define UI_EXTRACT_VIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_extract_vis
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *extract_vis)
    {
        if (extract_vis->objectName().isEmpty())
            extract_vis->setObjectName(QStringLiteral("extract_vis"));
        extract_vis->resize(699, 496);
        centralwidget = new QWidget(extract_vis);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 30, 661, 411));
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(20, 0, 101, 22));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(140, 0, 61, 23));
        extract_vis->setCentralWidget(centralwidget);
        menubar = new QMenuBar(extract_vis);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 699, 23));
        extract_vis->setMenuBar(menubar);
        statusbar = new QStatusBar(extract_vis);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        extract_vis->setStatusBar(statusbar);

        retranslateUi(extract_vis);

        QMetaObject::connectSlotsByName(extract_vis);
    } // setupUi

    void retranslateUi(QMainWindow *extract_vis)
    {
        extract_vis->setWindowTitle(QApplication::translate("extract_vis", "MainWindow", nullptr));
        comboBox->setItemText(0, QApplication::translate("extract_vis", "AAC", nullptr));
        comboBox->setItemText(1, QApplication::translate("extract_vis", "CKSAAP", nullptr));
        comboBox->setItemText(2, QApplication::translate("extract_vis", "N5C5_AAC", nullptr));

        pushButton->setText(QApplication::translate("extract_vis", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class extract_vis: public Ui_extract_vis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTRACT_VIS_H
