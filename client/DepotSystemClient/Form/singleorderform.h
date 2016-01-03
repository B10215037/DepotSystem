#ifndef SINGLEORDERFORM_H
#define SINGLEORDERFORM_H

#include <QWidget>
#include <qdebug.h>
#include "form.h"
#include "../Account/ManagerAccount.h"
#include "NewProductDialog.h"

namespace Ui {
class SingleOrderForm;
}

class SingleOrderForm : public Form
{
    Q_OBJECT

public:
    explicit SingleOrderForm(QWidget *parent = 0);
    ~SingleOrderForm();

signals:
    void transferOrderSignal(QList<Item>, QList<QString>);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void showProductSingleOrderResult(QList<Product>);

private:
    Ui::SingleOrderForm *ui;
    QList<QString> idList;
};

#endif // SINGLEORDERFORM_H
