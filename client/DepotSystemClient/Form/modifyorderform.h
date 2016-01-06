#ifndef MODIFYORDERFORM_H
#define MODIFYORDERFORM_H

#include <QDialog>
#include <qdebug.h>
#include "form/form.h"
#include "../Order/Order.h"
#include <QStandardItemModel>
#include <QLabel>


namespace Ui {
class ModifyOrderForm;
}

class ModifyOrderForm : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyOrderForm(QWidget *parent = 0);
    ~ModifyOrderForm();
    QList<Product> productList;

signals:
	void modifyOk(Order);

private slots:
    void transferOrderModifySlot(Order);
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ModifyOrderForm *ui;
    Order targetOrder;
    QString returnProductName(QString);

    //Popup dialog
    QDialog* dialog;
    QPushButton *confirmButton;
};

#endif // MODIFYORDERFORM_H
