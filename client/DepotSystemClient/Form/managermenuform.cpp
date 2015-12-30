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

void ManagerMenuForm::on_pushButton_clicked() //貨物管理
{
    emit getProductsInfoSignal();
    emit changeWindow(ManagerMenu, ProductManagement);
}

void ManagerMenuForm::on_pushButton_2_clicked() //收取訂單
{
    emit getOrdersInfoSignal();
    emit changeWindow(ManagerMenu, OrderManagement);
}

void ManagerMenuForm::on_pushButton_3_clicked() //登出
{
    emit logOutSignal();
    emit changeWindow(ManagerMenu, Login);
}
