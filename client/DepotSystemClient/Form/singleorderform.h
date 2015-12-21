#ifndef SINGLEORDERFORM_H
#define SINGLEORDERFORM_H

#include <QWidget>
#include "form.h"

namespace Ui {
class SingleOrderForm;
}

class SingleOrderForm : public Form
{
    Q_OBJECT

public:
    explicit SingleOrderForm(QWidget *parent = 0);
    ~SingleOrderForm();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SingleOrderForm *ui;
};

#endif // SINGLEORDERFORM_H
