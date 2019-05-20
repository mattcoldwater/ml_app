// Haoyu Wu
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <map>
#include <vector>
#include <string>
#include <QDebug>
using namespace std;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QString model_name;

    map<string, vector<QString>> data;

signals:
    void sendData(map<string, vector<QString>>);

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void sendModelBack();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
