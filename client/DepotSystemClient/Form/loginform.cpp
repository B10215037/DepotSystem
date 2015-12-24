#include "LogInForm.h"
#include "ui_LogInForm.h"
#include "userview.h"

LogInForm::LogInForm(QWidget *parent) :
    Form(parent),
    ui(new Ui::LogInForm)
{
    ui->setupUi(this);
}

LogInForm::~LogInForm()
{
    delete ui;
}

void LogInForm::on_pushButton_clicked()
{
    emit logInSignal(ui->lineEdit->text(), ui->lineEdit_2->text());
//    if (ui->lineEdit->text() == "m")
//        changeWindow(Login, ManagerMenu);
//    else
//        changeWindow(Login, CustomerMenu);
}

void LogInForm::showLogInResult(bool failed, QString message) {
    if (failed) {
//        ui->label_3->setText(message);
        emit showMessage(message, 10000);
    }
    else {
        ui->label_3->setText("");
        if (message == "Admin") emit changeWindow(Login, ManagerMenu);
        else emit changeWindow(Login, CustomerMenu);
    }
}
