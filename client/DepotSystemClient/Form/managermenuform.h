#ifndef MANAGERMENUFORM_H
#define MANAGERMENUFORM_H

#include <QWidget>
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

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ManagerMenuForm *ui;
};

#endif // MANAGERMENUFORM_H
