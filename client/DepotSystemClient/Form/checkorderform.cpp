#include "checkorderform.h"
#include "ui_checkorderform.h"

CheckOrderForm::CheckOrderForm(QWidget *parent) :
    Form(parent),
    ui(new Ui::CheckOrderForm)
{
  	curOrderIndex = -1;
    ui->setupUi(this);
    connect(ui->listView, SIGNAL(clicked(QModelIndex)),
    		this, SLOT(orderInfoDisplay(QModelIndex)));

}

CheckOrderForm::~CheckOrderForm()
{
    delete ui;
}

void CheckOrderForm::on_pushButton_clicked()
{
  	if(curOrderIndex > -1){
       ModifyOrderForm* modifyForm = new ModifyOrderForm(this);
       modifyForm->productList = productList;
       connect(this, SIGNAL(transferOrderModify(Order)),
               modifyForm, SLOT(transferOrderModifySlot(Order)));
       connect(modifyForm, SIGNAL(modifyOk(Order)),
               this, SLOT(modifyReturnOk(Order)));

       emit transferOrderModify(orderList[curOrderIndex]);
       modifyForm->exec();
  	}
    
}

void CheckOrderForm::on_pushButton_3_clicked()
{
    changeWindow(CheckOrder, CustomerMenu);
}

void CheckOrderForm::showOrdersSlot(QList<Order> orders){
  	orderList = orders;

    QStringListModel *model = new QStringListModel(this);
  	QStringList list;
  	for(int i = 0;i<orders.size();i++){
  		list << orders[i].getNumber();
  	}
  	model->setStringList(list);
    ui->listView->setModel(model);

}

void CheckOrderForm::productsInfoSlot(QList<Product> list){
    productList = list;
    qDebug()<<productList.size();
}

void CheckOrderForm::orderInfoDisplay(QModelIndex index){
    model = new QStandardItemModel(0, 2);
    model->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Amount"));

    ui->tableView->setModel(model);
    QList<Item> itemsTmp = orderList[index.row()].getItems();
    for (int i = 0; i < itemsTmp.size(); i++) {
        QStandardItem *name = new QStandardItem(returnProductName(itemsTmp[i].product)),
                	  *amount = new QStandardItem(QString::number(itemsTmp[i].amount));

        name->setEditable(false);
        amount->setEditable(false);

        ((QStandardItemModel*) ui->tableView->model())->setItem(i, 0, name);
        ((QStandardItemModel*) ui->tableView->model())->setItem(i, 1, amount);
    }
    ui->label_2->setText("State: " + orderList[index.row()].getState());
    // qDebug()<<orderList[index.row()].getState();
    if(orderList[index.row()].getState() != "archived"){
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
    }else{
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
    }
    curOrderIndex = index.row();
}

void CheckOrderForm::modifyReturnOk(Order order){
    // qDebug() << order.getItems()[0].product;
    emit putSignal(order);
}

QString CheckOrderForm::returnProductName(QString pid){
    for(int i = 0;i<productList.size();i++){
        if(productList[i].getID() == pid){
            return productList[i].getName();
        }
    }
    return "";
}
