// Haoyu Wu
#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QTextBrowser>

class ShowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShowWidget(QWidget *parent = 0);
    QTextBrowser *text;

signals:
public slots:
};

#endif // SHOWWIDGET_H
