/********************************************************************************
** Form generated from reading UI file 'model_evaluation_visualization.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODEL_EVALUATION_VISUALIZATION_H
#define UI_MODEL_EVALUATION_VISUALIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_model_evaluation_visualization
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *model_evaluation_visualization)
    {
        if (model_evaluation_visualization->objectName().isEmpty())
            model_evaluation_visualization->setObjectName(QStringLiteral("model_evaluation_visualization"));
        model_evaluation_visualization->resize(800, 600);
        menubar = new QMenuBar(model_evaluation_visualization);
        menubar->setObjectName(QStringLiteral("menubar"));
        model_evaluation_visualization->setMenuBar(menubar);
        centralwidget = new QWidget(model_evaluation_visualization);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        model_evaluation_visualization->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(model_evaluation_visualization);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        model_evaluation_visualization->setStatusBar(statusbar);

        retranslateUi(model_evaluation_visualization);

        QMetaObject::connectSlotsByName(model_evaluation_visualization);
    } // setupUi

    void retranslateUi(QMainWindow *model_evaluation_visualization)
    {
        model_evaluation_visualization->setWindowTitle(QApplication::translate("model_evaluation_visualization", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class model_evaluation_visualization: public Ui_model_evaluation_visualization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODEL_EVALUATION_VISUALIZATION_H
