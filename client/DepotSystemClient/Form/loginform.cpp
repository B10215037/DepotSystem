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
}

void LogInForm::showLogInResult(QString message) {
    ui->label_3->setText(message);
}
