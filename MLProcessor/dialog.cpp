// Haoyu Wu
#include "dialog.h"
#include "ui_dialog.h"
using namespace std;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    model_name = "tree";
    vector<QString> app_name, app_data;
    app_name.push_back("prediction");
    data.insert(pair<string,vector<QString>>("app_name",app_name));
    data.insert(pair<string,vector<QString>>("app_data",app_data));
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(sendModelBack()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_comboBox_currentIndexChanged(const QString &arg1)
{
    model_name = arg1;
}

void Dialog::sendModelBack()
{
    data["app_data"].push_back(model_name);
    data["app_data"].push_back(ui->textEdit->toPlainText());
    emit sendData(data);
}
