#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include "form.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public Form
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_H
