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
    QList<Item>  itemList;
    QList<QString> nameList;
    for(int i = 0;i<idList.size();i++){
        QModelIndex index = ((QStandardItemModel*) ui->tableView->model())->index(i,2,QModelIndex());
        int curAmount = ((QStandardItemModel*) ui->tableView->model())->data(index).toInt();
        if(curAmount > 0){
        	itemList.push_back(Item(idList[i], curAmount));
        	index = ((QStandardItemModel*) ui->tableView->model())->index(i,0,QModelIndex());
        	QString curName = ((QStandardItemModel*) ui->tableView->model())->data(index).toString();
        	nameList.push_back(curName);
        }

    }
    if(itemList.size() > 0){

        emit transferOrderSignal(itemList, nameList);
        changeWindow(SingleOrder, ConfirmOrder);
    }else{

    }
}

void SingleOrderForm::on_pushButton_2_clicked()
{
    changeWindow(SingleOrder, CustomerMenu);
}

void SingleOrderForm::showProductSingleOrderResult(QList<Product> products) {
    QStandardItemModel *model = new QStandardItemModel(0, 3);
    model->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Price"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Quantity"));
    ui->tableView->setModel(model);

    for (int i = 0; i < products.size(); i++) {
        QStandardItem *name = new QStandardItem(products[i].getName()),
                	  *price = new QStandardItem(QString::number(products[i].getPrice())),
                	  *quantity = new QStandardItem();

        idList.push_back(products[i].getID());

        name->setEditable(false);
        price->setEditable(false);
        quantity->setEditable(true);

        ((QStandardItemModel*) ui->tableView->model())->setItem(i, 0, name);
        ((QStandardItemModel*) ui->tableView->model())->setItem(i, 1, price);
        ((QStandardItemModel*) ui->tableView->model())->setItem(i, 2, quantity);
    }
}
