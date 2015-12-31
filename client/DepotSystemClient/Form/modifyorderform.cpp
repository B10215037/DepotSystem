#include "modifyorderform.h"
#include "ui_modifyorderform.h"

ModifyOrderForm::ModifyOrderForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyOrderForm)
{
    ui->setupUi(this);
}

ModifyOrderForm::~ModifyOrderForm()
{
    delete ui;
}



void ModifyOrderForm::transferOrderModifySlot(Order order){
	QStandardItemModel *model = new QStandardItemModel(0, 2);
    model->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Amount"));
    ui->tableView->setModel(model);
    QList<Item> items = order.getItems();
    for (int i = 0; i < items.size(); i++) {
        QStandardItem *name = new QStandardItem(items[i].product),
                	  *amount = new QStandardItem(QString::number(items[i].amount));

        name->setEditable(false);
        amount->setEditable(true);

        ((QStandardItemModel*) ui->tableView->model())->setItem(i, 0, name);
        ((QStandardItemModel*) ui->tableView->model())->setItem(i, 1, amount);
    }
    targetOrder = order;
}
void ModifyOrderForm::on_pushButton_2_clicked()
{
    close();
}

void ModifyOrderForm::on_pushButton_clicked()
{
    for(int i = 0;i<targetOrder.getItems().size();i++){
        QModelIndex index = ((QStandardItemModel*) ui->tableView->model())->index(i,1,QModelIndex());
        int curAmount = ((QStandardItemModel*) ui->tableView->model())->data(index).toInt();
    	targetOrder.setItemAmount(targetOrder.getItems()[i].product, curAmount);
    }
    emit modifyOk(targetOrder);
    close();
}
