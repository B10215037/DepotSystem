#ifndef MANAGERMENUFORM_H
#define MANAGERMENUFORM_H

#include "form.h"

namespace Ui {
class ManagerMenuForm;
}

class ManagerMenuForm : public Form
{
    Q_OBJECT

public:
    explicit ManagerMenuForm(QWidget *parent = 0);
    ~ManagerMenuForm();

signals:
    void logOutSignal();
    void getProductsInfoSignal();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::ManagerMenuForm *ui;
};

#endif // MANAGERMENUFORM_H
