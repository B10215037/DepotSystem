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

    QString txt = "確認修改以下資料?\n新增:\n";
    int size = account.newProducts.size();
    if (size == 0) txt += "無\n";
    for (int i = 0; i < size; i++)
        txt += "name:" + account.newProducts[i].getName() + "\n" +
                "stock:" + QString::number(account.newProducts[i].getStock()) + "\n" +
                "price:" + QString::number(account.newProducts[i].getPrice()) + "\n";

    txt += "更改:\n";
    size = account.editedProducts.size();
    if (size == 0) txt += "無\n";
    for (int i = 0; i < size; i++)
        txt += "name:" + account.editedProducts[i].getName() + "\n" +
                "stock:" + QString::number(account.editedProducts[i].getStock()) +"\n" +
                "price:" + QString::number(account.editedProducts[i].getPrice()) + "\n";

    txt += "刪除:\n";
    size = account.deletedProducts.size();
    if (size == 0) txt += "無\n";
    for (int i = 0; i < size; i++)
        txt += "name:" + account.deletedProducts[i].getName() + "\n";
    dialog->setText(txt);

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
    account.newProducts.clear();
    account.editedProducts.clear();
    account.deletedProducts.clear();
    if (ui->tableView->model()) delete ui->tableView->model();

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

void ProductManagementForm::on_pushButton_4_clicked() //刪除貨物
{
    QModelIndexList index = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < index.size(); i++) {
        QString id = index[i].data().toString(),
                name = ui->tableView->model()->index(index[i].row(), 1).data().toString();

        if (id == "尚未有ID") {
            for (int i = 0; i < account.newProducts.size(); i++)
                if (account.newProducts[i].getName() == name) {
                    account.newProducts.removeAt(i);
                    break;
                }
        }
        else {
            for (int i = 0; i < account.editedProducts.size(); i++) {
                if (account.editedProducts[i].getID() == id) {
                    account.editedProducts.removeAt(i);
                    break;
                }
            }
            Product p = Product(id);
            p.setName(name);
            account.deletedProducts.append(p);
        }
    }

    while (index.size()) {
        ui->tableView->model()->removeRow(index[0].row());
        index = ui->tableView->selectionModel()->selectedRows();
    }
}

void ProductManagementForm::addNewProduct(QString name, int stock, int price) { //接收新貨物
    setEnabled(true);

    if (name == "") {
        QMessageBox *dialog = new QMessageBox;
        dialog->setText("新增失敗，名稱不可為空!");
        dialog->setWindowFlags(Qt::CustomizeWindowHint);
        dialog->setStandardButtons(QMessageBox::Ok);
        connect(dialog->button(QMessageBox::Ok), SIGNAL(clicked()), this, SLOT(recycle()));
        widgetRecycleContainer.append(dialog);
        dialog->show();
        return;
    }

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

    Product p = Product(); //不用ID
    p.setName(name);
    p.setStock(stock);
    p.setPrice(price);
    account.newProducts.append(p);

    setTableView("尚未有ID", name, stock, price);
}

void ProductManagementForm::editProduct(QModelIndex index, QString oldName) { //編輯確認後
    setEnabled(true);

    QString id = ui->tableView->model()->index(index.row(), 0).data().toString(),
            name = ui->tableView->model()->index(index.row(), 1).data().toString();
    int row = ui->tableView->model()->rowCount(),
            stock = ui->tableView->model()->index(index.row(), 2).data().toInt(),
            price = ui->tableView->model()->index(index.row(), 3).data().toInt();

    for (int i = 0; i < row; i++)
        if (name == ui->tableView->model()->index(i, 1).data().toString() && index.row() != i) {
            QMessageBox *dialog = new QMessageBox;
            dialog->setText(name + "修改失敗，已有相同名稱的貨物!");
            dialog->setWindowFlags(Qt::CustomizeWindowHint);
            dialog->setStandardButtons(QMessageBox::Ok);
            connect(dialog->button(QMessageBox::Ok), SIGNAL(clicked()), this, SLOT(recycle()));
            widgetRecycleContainer.append(dialog);
            dialog->show();
            return;
        }

    if (ui->tableView->model()->index(index.row(), 0).data().toString() == "尚未有ID") {
        for (int i = 0; i < account.newProducts.size(); i++) {
            qDebug()<<"DFFD"<<account.newProducts[i].getName()<<"DF"<<oldName;
            if (account.newProducts[i].getName() == oldName) {
                account.newProducts[i].setName(name);
                account.newProducts[i].setStock(stock);
                account.newProducts[i].setPrice(price);
                return;
            }
        }
    }
    else {
        for (int i = 0; i < account.editedProducts.size(); i++) {
            if (account.editedProducts[i].getID() == id) {
                account.editedProducts[i].setName(name);
                account.editedProducts[i].setStock(stock);
                account.editedProducts[i].setPrice(price);
                return;
            }
        }
        Product p = Product(id);
        p.setName(name);
        p.setStock(stock);
        p.setPrice(price);
        account.editedProducts.append(p);
    }
}

void ProductManagementForm::tableItemChanged(QModelIndex index) { //編輯觸發
    if (index.column() == 0 || !isEnabled()) return;
    setEnabled(false);

    NewProductDialog *editProductDialog = new NewProductDialog(index);
    connect(editProductDialog, SIGNAL(confirmEditedProduct(QModelIndex,QString)),
            this, SLOT(editProduct(QModelIndex,QString)));
    connect(editProductDialog, SIGNAL(cancel()),
            this, SLOT(recycle()));
    editProductDialog->show();
}

void ProductManagementForm::recycle() {
    setEnabled(true);
    while (widgetRecycleContainer.size()) delete widgetRecycleContainer.takeAt(0);
}

void ProductManagementForm::recycleAndConfirmUpdate() { //更新貨物請求
    emit updateProductsSignal(account.newProducts, account.editedProducts, account.deletedProducts);

    account.newProducts.clear();
    account.editedProducts.clear();
    account.deletedProducts.clear();
    recycle();
}

void ProductManagementForm::showProductManagementResult(QList<Product> products) {
    QStandardItemModel *model = new QStandardItemModel(0, 4);
    model->setHorizontalHeaderItem(0, new QStandardItem("ID"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Name"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Stock"));
    model->setHorizontalHeaderItem(3, new QStandardItem("Price"));
    ui->tableView->setModel(model);
    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(tableItemChanged(QModelIndex)));

    for (int i = 0; i < products.size(); i++) {
        QStandardItem *id = new QStandardItem(products[i].getID()),
                *name = new QStandardItem(products[i].getName()),
                *stock = new QStandardItem(QString::number(products[i].getStock())),
                *price = new QStandardItem(QString::number(products[i].getPrice()));
        id->setEditable(false);
        name->setEditable(false);
        stock->setEditable(false);
        price->setEditable(false);

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
    nameItem->setEditable(false);
    stockItem->setEditable(false);
    priceItem->setEditable(false);

    int row = ui->tableView->model()->rowCount();
    ((QStandardItemModel*) ui->tableView->model())->setItem(row, 0, idItem);
    ((QStandardItemModel*) ui->tableView->model())->setItem(row, 1, nameItem);
    ((QStandardItemModel*) ui->tableView->model())->setItem(row, 2, stockItem);
    ((QStandardItemModel*) ui->tableView->model())->setItem(row, 3, priceItem);
}
