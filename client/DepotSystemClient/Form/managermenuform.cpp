#include "managermenuform.h"
#include "ui_managermenuform.h"

ManagerMenuForm::ManagerMenuForm(QWidget *parent) :
    Form(parent),
    ui(new Ui::ManagerMenuForm)
{
    ui->setupUi(this);
}

ManagerMenuForm::~ManagerMenuForm()
{
    delete ui;
}

void ManagerMenuForm::on_pushButton_clicked()
{
    emit getProductsInfoSignal();
    emit changeWindow(ManagerMenu, ProductManagement);
}

void ManagerMenuForm::on_pushButton_2_clicked()
{
    emit changeWindow(ManagerMenu, OrderManagement);
}

void ManagerMenuForm::on_pushButton_3_clicked()
{
    emit logOutSignal();
    emit changeWindow(ManagerMenu, Login);
}
