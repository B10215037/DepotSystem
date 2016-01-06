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
        QStandardItem *name = new QStandardItem(returnProductName(items[i].product)),
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
    bool isValid = true;
    for(int i = 0;i<targetOrder.getItems().size();i++){
        QModelIndex index = ((QStandardItemModel*) ui->tableView->model())->index(i,1,QModelIndex());
        int curAmount = ((QStandardItemModel*) ui->tableView->model())->data(index).toInt(&isValid);
        if (!isValid)   break;
    	targetOrder.setItemAmount(targetOrder.getItems()[i].product, curAmount);
    }
    if(isValid){
        emit modifyOk(targetOrder);
        close();
    }else{
        dialog = new QDialog(this, Qt::Popup);
        confirmButton = new QPushButton(dialog);
        dialog->setSizeIncrement(QSize(200, 70));
        confirmButton->setGeometry(QRect(70, 20, 60, 30));
        confirmButton->setText("確認");
        connect(confirmButton, SIGNAL(clicked()),
                dialog, SLOT(close()));
        QLabel *content = new QLabel("Invalid input!" ,dialog);

        dialog->show();
    }
}

QString ModifyOrderForm::returnProductName(QString pid){
    for(int i = 0;i<productList.size();i++){
        if(productList[i].getID() == pid){
            return productList[i].getName();
        }
    }
    return "";
}
