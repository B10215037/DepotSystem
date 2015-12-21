#include "productmanagementform.h"
#include "ui_productmanagementform.h"

ProductManagementForm::ProductManagementForm(QWidget *parent) :
    Form(parent),
    ui(new Ui::ProductManagementForm)
{
    ui->setupUi(this);

    QStandardItemModel *model = new QStandardItemModel(0, 4);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Stock")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("price")));
    ui->tableView->setModel(model);
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
    for (int i = 0; i < products.size(); i++) {
        QStandardItem *item = new QStandardItem;
        item->setColumnCount(4);
        item->setChild(i, new QStandardItem(products[i].getID()));
        item->setChild(i, new QStandardItem(products[i].getName()));
        item->setChild(i, new QStandardItem(products[i].getStock()));
        item->setChild(i, new QStandardItem(products[i].getPrice()));
        ((QStandardItemModel*) ui->tableView->model())->setItem(i, item);
    }
}
