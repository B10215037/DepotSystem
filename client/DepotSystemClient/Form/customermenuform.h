#ifndef CUSTOMERMENUFORM_H
#define CUSTOMERMENUFORM_H

#include <QWidget>
#include "form.h"

namespace Ui {
class CustomerMenuForm;
}

class CustomerMenuForm : public Form
{
    Q_OBJECT

public:
    explicit CustomerMenuForm(QWidget *parent = 0);
    ~CustomerMenuForm();

signals:
    void logOutSignal();
    void getProductsInfoSignal();
    void getOrdersInfoSignal();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::CustomerMenuForm *ui;
};

#endif // CUSTOMERMENUFORM_H
