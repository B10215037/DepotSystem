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
    changeWindow(CustomerMenu, Login);
}
