#include "customermenuform.h"
#include "ui_customermenuform.h"

CustomerMenuForm::CustomerMenuForm(QWidget *parent) :
    Form(parent),
    ui(new Ui::CustomerMenuForm)
{
    ui->setupUi(this);
}

CustomerMenuForm::~CustomerMenuForm()
{
    delete ui;
}

void CustomerMenuForm::on_pushButton_3_clicked()
{
    emit logOutSignal();
    changeWindow(CustomerMenu, Login);
}

void CustomerMenuForm::on_pushButton_clicked()
{
    changeWindow(CustomerMenu, SingleOrder);
}

void CustomerMenuForm::on_pushButton_2_clicked()
{
    changeWindow(CustomerMenu, CheckOrder);
}
