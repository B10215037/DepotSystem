#ifndef CHECKORDERFORM_H
#define CHECKORDERFORM_H

#include <QWidget>
#include "form.h"

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


private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::CheckOrderForm *ui;
};

#endif // CHECKORDERFORM_H
