#ifndef CHECKORDERFORM_H
#define CHECKORDERFORM_H

#include <QWidget>
#include "form.h"
#include "../Order/Order.h"
#include <QStringListModel>
#include <qdebug.h>
#include <QStandardItemModel>
#include <form/modifyorderform.h>

namespace Ui {
class CheckOrderForm;
}

class CheckOrderForm : public Form
{
    Q_OBJECT

public:
    explicit CheckOrderForm(QWidget *parent = 0);
    ~CheckOrderForm();

signals:
    void transferOrderModify(Order);
    void putSignal(Order);
    void getProductsInfoSignal();
    void deleteOrderSignal(Order);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void showOrdersSlot(QList<Order>);
    void orderInfoDisplay(QModelIndex);
    void modifyReturnOk(Order);
    void productsInfoSlot(QList<Product>);
    void clearDisplaySlot();

    void on_pushButton_2_clicked();

private:
    Ui::CheckOrderForm *ui;
    QList<Order> orderList;
    QStandardItemModel *model;	//tableView
    int curOrderIndex;
    QList<Product> productList; //Used for finding corresponding name
    QString returnProductName(QString); 
    
};

#endif // CHECKORDERFORM_H
