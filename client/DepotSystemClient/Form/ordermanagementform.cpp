#include "ordermanagementform.h"
#include "ui_ordermanagementform.h"
#include<QDebug>

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

void OrderManagementForm::on_pushButton_clicked() //接受顧客的訂單
{
    QModelIndexList list = ui->treeView->selectionModel()->selectedIndexes();
    if (list.size() == 0) return;
    if (list[0].data().toString().left(6) != "訂單ID: " ||
            list[0].parent().data().toString() != "尚未處理的訂單") return;

    Order order(list[0].data().toString().split("訂單ID: ")[1]);
    order.setState("processing");
    emit acceptOrderOrNotSignal(order);

    if (ui->treeView->model()) delete ui->treeView->model();
}

void OrderManagementForm::on_pushButton_2_clicked() //拒絕顧客的訂單
{
    QModelIndexList list = ui->treeView->selectionModel()->selectedIndexes();
    if (list.size() == 0) return;
    if (list[0].data().toString().left(6) != "訂單ID: " ||
            list[0].parent().data().toString() != "尚未處理的訂單") return;

    Order order(list[0].data().toString().split("訂單ID: ")[1]);
    order.setState("rejected");
    emit acceptOrderOrNotSignal(order);

    if (ui->treeView->model()) delete ui->treeView->model();
}

void OrderManagementForm::on_pushButton_3_clicked() //返回
{
    changeWindow(OrderManagement, ManagerMenu);

    if (ui->treeView->model()) delete ui->treeView->model();
}

void OrderManagementForm::showOrderManagementResult(QList<Order> orders_taken,
                                                    QList<Order> orders_notTaken,
                                                    QList<Order> orders_notITake) {
    QStandardItemModel *model = new QStandardItemModel();
    QStandardItem *row1 = new QStandardItem("尚未處理的訂單"),
            *row2 = new QStandardItem("我處理的訂單"),
            *row3 = new QStandardItem("別人處理的訂單");
    row1->setEditable(false);
    row2->setEditable(false);
    row3->setEditable(false);
    model->setItem(0, row1);
    model->setItem(1, row2);
    model->setItem(2, row3);
    ui->treeView->setModel(model);

    for (int i = 0; i < orders_notTaken.size(); i++) { //尚未處理的訂單
        QStandardItem *id = new QStandardItem("訂單ID: " + orders_notTaken[i].getNumber()),
                *name = new QStandardItem("下訂者: " + orders_notTaken[i].getWhoOrdered()),
                *state = new QStandardItem("狀態: " + orders_notTaken[i].getState()),
                *product = new QStandardItem("購買產品:");
        id->setEditable(false);
        name->setEditable(false);
        state->setEditable(false);
        product->setEditable(false);

        QList<Item> items = orders_notTaken[i].getItems();
        for (int j = 0; j < items.size(); ++j) {
            QStandardItem *itemId = new QStandardItem("產品ID: " + items[j].product);
            QStandardItem *itemAmount = new QStandardItem("數量: " + QString::number(items[j].amount));
            itemId->setEditable(false);
            itemAmount->setEditable(false);
            product->setChild(j, itemId);
            itemId->setChild(0, itemAmount);
        }

        row1->setChild(i, id);
        id->setChild(0, name);
        id->setChild(1, state);
        id->setChild(2, product);
    }

    for (int i = 0; i < orders_taken.size(); i++) { //我處理的訂單 + 別人處理的訂單
        QStandardItem *id = new QStandardItem("訂單ID: " + orders_taken[i].getNumber()),
                *name = new QStandardItem("下訂者: " + orders_taken[i].getWhoOrdered()),
                *state = new QStandardItem("狀態: " + orders_taken[i].getState()),
                *product = new QStandardItem("購買產品:");
        id->setEditable(false);
        name->setEditable(false);
        state->setEditable(false);
        product->setEditable(false);

        QList<Item> items = orders_taken[i].getItems();
        for (int j = 0; j < items.size(); ++j) {
            QStandardItem *itemId = new QStandardItem("產品ID: " + items[j].product);
            QStandardItem *itemAmount = new QStandardItem("數量: " + QString::number(items[j].amount));
            itemId->setEditable(false);
            itemAmount->setEditable(false);
            product->setChild(j, itemId);
            itemId->setChild(0, itemAmount);
        }

        row2->setChild(i, id);
        id->setChild(0, name);
        id->setChild(1, state);
        id->setChild(2, product);
    }

    for (int i = 0; i < orders_notITake.size(); i++) { //我處理的訂單 + 別人處理的訂單
        QStandardItem *id = new QStandardItem("訂單ID: " + orders_notITake[i].getNumber()),
                *name = new QStandardItem("下訂者: " + orders_notITake[i].getWhoOrdered()),
                *state = new QStandardItem("狀態: " + orders_notITake[i].getState()),
                *product = new QStandardItem("購買產品:");
        id->setEditable(false);
        name->setEditable(false);
        state->setEditable(false);
        product->setEditable(false);

        QList<Item> items = orders_notITake[i].getItems();
        for (int j = 0; j < items.size(); ++j) {
            QStandardItem *itemId = new QStandardItem("產品ID: " + items[j].product);
            QStandardItem *itemAmount = new QStandardItem("數量: " + QString::number(items[j].amount));
            itemId->setEditable(false);
            itemAmount->setEditable(false);
            product->setChild(j, itemId);
            itemId->setChild(0, itemAmount);
        }

        row2->setChild(i, id);
        id->setChild(0, name);
        id->setChild(1, state);
        id->setChild(2, product);
    }
}
