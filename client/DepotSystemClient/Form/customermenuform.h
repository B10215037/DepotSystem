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

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::CustomerMenuForm *ui;
};

#endif // CUSTOMERMENUFORM_H
