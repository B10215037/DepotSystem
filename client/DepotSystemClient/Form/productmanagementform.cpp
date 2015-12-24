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

void ProductManagementForm::showProductManagementResult(QList<Product> products) {
    if (ui->tableView->model()) delete ui->tableView->model();

    QStandardItemModel *model = new QStandardItemModel(0, 4);
    model->setHorizontalHeaderItem(0, new QStandardItem("ID"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Name"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Stock"));
    model->setHorizontalHeaderItem(3, new QStandardItem("price"));
    ui->tableView->setModel(model);

    for (int i = 0; i < products.size(); i++) {
        QStandardItem *item = new QStandardItem(products[i].getID()),
                *name = new QStandardItem(products[i].getName()),
                *stock = new QStandardItem(QString::number(products[i].getStock())),
                *price = new QStandardItem(QString::number(products[i].getPrice()));

        ((QStandardItemModel*) ui->tableView->model())->setItem(i, 0, item);
        ((QStandardItemModel*) ui->tableView->model())->setItem(i, 1, name);
        ((QStandardItemModel*) ui->tableView->model())->setItem(i, 2, stock);
        ((QStandardItemModel*) ui->tableView->model())->setItem(i, 3, price);
    }
}
