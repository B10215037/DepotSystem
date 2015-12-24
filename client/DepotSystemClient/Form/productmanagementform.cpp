#include "productmanagementform.h"
#include "ui_productmanagementform.h"
#include <QDebug>

ProductManagementForm::ProductManagementForm(QWidget *parent) :
    Form(parent),
    ui(new Ui::ProductManagementForm)
{
    ui->setupUi(this);
    account = ManagerAccount();
}

ProductManagementForm::~ProductManagementForm()
{
    delete ui;
}

void ProductManagementForm::on_pushButton_clicked() //確定修改
{
    setEnabled(false);

    QMessageBox *dialog = new QMessageBox;

    dialog->setText("確認修改以下資料?");
///todo print data
    dialog->setWindowFlags(Qt::CustomizeWindowHint);
    dialog->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    connect(dialog->button(QMessageBox::Ok), SIGNAL(clicked()),
            this, SLOT(recycleAndConfirmUpdate()));
    connect(dialog->button(QMessageBox::Cancel), SIGNAL(clicked()),
            this, SLOT(recycle()));
    widgetRecycleContainer.append(dialog);
    dialog->show();
}

void ProductManagementForm::on_pushButton_2_clicked() //返回
{
    changeWindow(ProductManagement, ManagerMenu);
}

void ProductManagementForm::on_pushButton_3_clicked() //新增貨物
{
    setEnabled(false);

    NewProductDialog *newProductDialog = new NewProductDialog;
    connect(newProductDialog, SIGNAL(confirmNewProduct(QString,int,int)),
            this, SLOT(addNewProduct(QString,int,int)));
    connect(newProductDialog, SIGNAL(cancel()),
            this, SLOT(recycle()));
    newProductDialog->show();
}

void ProductManagementForm::addNewProduct(QString name, int stock, int price) { //接收新貨物
    setEnabled(true);

    int row = ui->tableView->model()->rowCount();
    for (int i = 0; i < row; i++)
        if (name == ui->tableView->model()->index(i, 1).data().toString()) {
            QMessageBox *dialog = new QMessageBox;
            dialog->setText(name + "新增失敗，已有相同名稱的貨物!");
            dialog->setWindowFlags(Qt::CustomizeWindowHint);
            dialog->setStandardButtons(QMessageBox::Ok);
            connect(dialog->button(QMessageBox::Ok), SIGNAL(clicked()), this, SLOT(recycle()));
            widgetRecycleContainer.append(dialog);
            dialog->show();
            return;
        }

    Product p = Product();
    p.setName(name);
    p.setStock(stock);
    p.setPrice(price);
    account.newProducts.append(p);

    setTableView("?", name, stock, price);
}

void ProductManagementForm::recycle() {
    setEnabled(true);
    while (widgetRecycleContainer.size()) delete widgetRecycleContainer.takeAt(0);
}

void ProductManagementForm::recycleAndConfirmUpdate() { //更新貨物請求
    emit updateProductsSignal(account.newProducts, account.changedProducts, account.deletedProducts);

    account.newProducts.clear();
    account.changedProducts.clear();
    account.deletedProducts.clear();
    recycle();
}

void ProductManagementForm::on_pushButton_5_clicked() //刪除貨物
{
    QModelIndexList index = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < index.size(); i++) {
        account.deletedProducts.append(Product(index[i].data().toString()));
        ui->tableView->model()->removeRow(index[i].row());
    }
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
        QStandardItem *id = new QStandardItem(products[i].getID()),
                *name = new QStandardItem(products[i].getName()),
                *stock = new QStandardItem(QString::number(products[i].getStock())),
                *price = new QStandardItem(QString::number(products[i].getPrice()));
        id->setEditable(false);

        ((QStandardItemModel*) ui->tableView->model())->setItem(i, 0, id);
        ((QStandardItemModel*) ui->tableView->model())->setItem(i, 1, name);
        ((QStandardItemModel*) ui->tableView->model())->setItem(i, 2, stock);
        ((QStandardItemModel*) ui->tableView->model())->setItem(i, 3, price);
    }
}

void ProductManagementForm::setTableView(QString id, QString name, int stock, int price) {
    if (!(ui->tableView->model())) {
        QStandardItemModel *model = new QStandardItemModel(0, 4);
        model->setHorizontalHeaderItem(0, new QStandardItem("ID"));
        model->setHorizontalHeaderItem(1, new QStandardItem("Name"));
        model->setHorizontalHeaderItem(2, new QStandardItem("Stock"));
        model->setHorizontalHeaderItem(3, new QStandardItem("price"));
        ui->tableView->setModel(model);
    }

    QStandardItem *idItem = new QStandardItem(id),
            *nameItem = new QStandardItem(name),
            *stockItem = new QStandardItem(QString::number(stock)),
            *priceItem = new QStandardItem(QString::number(price));
    idItem->setEditable(false);

    int row = ui->tableView->model()->rowCount();
    ((QStandardItemModel*) ui->tableView->model())->setItem(row, 0, idItem);
    ((QStandardItemModel*) ui->tableView->model())->setItem(row, 1, nameItem);
    ((QStandardItemModel*) ui->tableView->model())->setItem(row, 2, stockItem);
    ((QStandardItemModel*) ui->tableView->model())->setItem(row, 3, priceItem);
}
