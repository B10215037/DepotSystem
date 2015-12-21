#ifndef CONFIRMORDERFORM_H
#define CONFIRMORDERFORM_H

#include <QWidget>
#include "form.h"

namespace Ui {
class ConfirmOrderForm;
}

class ConfirmOrderForm : public Form
{
    Q_OBJECT

public:
    explicit ConfirmOrderForm(QWidget *parent = 0);
    ~ConfirmOrderForm();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ConfirmOrderForm *ui;
};

#endif // CONFIRMORDERFORM_H
