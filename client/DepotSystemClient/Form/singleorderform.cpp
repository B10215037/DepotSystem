#include "singleorderform.h"
#include "ui_singleorderform.h"

SingleOrderForm::SingleOrderForm(QWidget *parent) :
    Form(parent),
    ui(new Ui::SingleOrderForm)
{
    ui->setupUi(this);
}

SingleOrderForm::~SingleOrderForm()
{
    delete ui;
}

void SingleOrderForm::on_pushButton_clicked()
{
    changeWindow(SingleOrder, ConfirmOrder);
}

void SingleOrderForm::on_pushButton_2_clicked()
{
    changeWindow(SingleOrder, CustomerMenu);
}
