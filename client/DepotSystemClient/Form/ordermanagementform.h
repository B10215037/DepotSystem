#ifndef ORDERMANAGEMENTFORM_H
#define ORDERMANAGEMENTFORM_H

#include <QWidget>
#include "form.h"

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

private:
    Ui::OrderManagementForm *ui;
};

#endif // ORDERMANAGEMENTFORM_H
