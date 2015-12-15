#include "ordermanagementform.h"
#include "ui_ordermanagementform.h"

OrderManagementForm::OrderManagementForm(QWidget *parent) :
    Form(parent),
    ui(new Ui::OrderManagementForm)
{
    ui->setupUi(this);
}

OrderManagementForm::~OrderManagementForm()
{
    delete ui;
}

void OrderManagementForm::on_pushButton_3_clicked()
{
    changeWindow(OrderManagement, ManagerMenu);
}
