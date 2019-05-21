// Haoyu Wu
#include "showwidget.h"
#include <QHBoxLayout>

ShowWidget::ShowWidget(QWidget *parent) : QWidget(parent)
{
    text = new QTextBrowser;
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(text);
}
