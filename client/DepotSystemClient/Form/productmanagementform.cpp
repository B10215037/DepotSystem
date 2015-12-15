#include "productmanagementform.h"
#include "ui_productmanagementform.h"

ProductManagementForm::ProductManagementForm(QWidget *parent) :
    Form(parent),
    ui(new Ui::ProductManagementForm)
{
    ui->setupUi(this);
}

ProductManagementForm::~ProductManagementForm()
{
    delete ui;
}

void ProductManagementForm::on_pushButton_clicked()
{
    changeWindow(ProductManagement, ManagerMenu);
}

void ProductManagementForm::on_pushButton_2_clicked()
{
    changeWindow(ProductManagement, ManagerMenu);
}
