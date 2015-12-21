#include "checkorderform.h"
#include "ui_checkorderform.h"

CheckOrderForm::CheckOrderForm(QWidget *parent) :
    Form(parent),
    ui(new Ui::CheckOrderForm)
{
    ui->setupUi(this);
}

CheckOrderForm::~CheckOrderForm()
{
    delete ui;
}

void CheckOrderForm::on_pushButton_clicked()
{
    changeWindow(CheckOrder, SingleOrder);
}

void CheckOrderForm::on_pushButton_3_clicked()
{
    changeWindow(CheckOrder, CustomerMenu);
}
