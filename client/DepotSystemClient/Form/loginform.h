#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include "form.h"

namespace Ui {
class LogInForm;
}

class LogInForm : public Form
{
    Q_OBJECT

public:
    explicit LogInForm(QWidget *parent = 0);
    ~LogInForm();

signals:
    void logInSignal(QString username, QString password);

private slots:
    void on_pushButton_clicked();
    void showLogInResult(QString message);

private:
    Ui::LogInForm *ui;
};

#endif // LOGINFORM_H
