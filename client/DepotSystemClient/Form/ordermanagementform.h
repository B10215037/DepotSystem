#ifndef ORDERMANAGEMENTFORM_H
#define ORDERMANAGEMENTFORM_H

#include <QWidget>
#include "form.h"
#include "../Order/Order.h"

namespace Ui {
class OrderManagementForm;
}

class OrderManagementForm : public Form
{
    Q_OBJECT

public:
    explicit OrderManagementForm(QWidget *parent = 0);
    ~OrderManagementForm();

private slots:
    void on_pushButton_3_clicked();

    void showOrderManagementResult(QList<Order> orders_taken, QList<Order> orders_notTaken);

private:
    Ui::OrderManagementForm *ui;
};

#endif // ORDERMANAGEMENTFORM_H
