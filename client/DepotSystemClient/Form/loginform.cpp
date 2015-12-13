#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    Form(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_pushButton_clicked()
{
    if (ui->lineEdit->text() == "m")
        changeWindow(Login, ManagerMenu);
    else
        changeWindow(Login, CustomerMenu);
}
