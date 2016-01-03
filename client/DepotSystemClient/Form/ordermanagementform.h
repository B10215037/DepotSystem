#ifndef ORDERMANAGEMENTFORM_H
#define ORDERMANAGEMENTFORM_H

#include <QWidget>
#include "form.h"
#include "../Order/Order.h"
#include <QStandardItemModel>

namespace Ui {
class OrderManagementForm;
}

class OrderManagementForm : public Form
{
    Q_OBJECT

public:
    explicit OrderManagementForm(QWidget *parent = 0);
    ~OrderManagementForm();

signals:
    void acceptOrderOrNotSignal(Order oeder);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void showOrderManagementResult(QList<Order> orders_taken,
                                   QList<Order> orders_notTaken,
                                   QList<Order> orders_notITake);

private:
    Ui::OrderManagementForm *ui;
};

#endif // ORDERMANAGEMENTFORM_H
