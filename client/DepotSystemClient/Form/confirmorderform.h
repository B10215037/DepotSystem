#ifndef CONFIRMORDERFORM_H
#define CONFIRMORDERFORM_H

#include <QWidget>
#include <qdebug.h>
#include "form.h"
#include "../Account/ManagerAccount.h"
#include "NewProductDialog.h"
#include <QDialog>
#include <QDialogButtonBox>

namespace Ui {
class ConfirmOrderForm;
}

class ConfirmOrderForm : public Form
{
    Q_OBJECT

public:
    explicit ConfirmOrderForm(QWidget *parent = 0);
    ~ConfirmOrderForm();

signals:
    void postOrdersInfoSignal(QList<Item>);

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void transferOrderSlot(QList<Item>, QList<QString>);
    void postValid(bool);
    void dialogDestructSlot(int);

private:
    Ui::ConfirmOrderForm *ui;
    void showConfirmedDialog();
    void showFailedDialog();
    QPushButton *confirmButton;
    QDialog* dialog;
    QList<Item>	orderList;
};

#endif // CONFIRMORDERFORM_H
