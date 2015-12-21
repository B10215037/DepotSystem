#include "confirmorderform.h"
#include "ui_confirmorderform.h"

ConfirmOrderForm::ConfirmOrderForm(QWidget *parent) :
    Form(parent),
    ui(new Ui::ConfirmOrderForm)
{
    ui->setupUi(this);
}

ConfirmOrderForm::~ConfirmOrderForm()
{
    delete ui;
}

void ConfirmOrderForm::on_pushButton_2_clicked()
{
    changeWindow(ConfirmOrder, SingleOrder);
}

void ConfirmOrderForm::on_pushButton_clicked()
{
    changeWindow(ConfirmOrder, CustomerMenu);
}
