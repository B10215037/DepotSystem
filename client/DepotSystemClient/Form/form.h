#ifndef FORM_H
#define FORM_H

#include <QWidget>

class Form : public QWidget
{
    Q_OBJECT
public:
    enum{
        Login = 0,
        CustomerMenu,
        ManagerMenu,
        ProductManagement,
        OrderManagement,
        CheckOrder,
        ConfirmOrder,
        SingleOrder,
        FORM_COUNT
    };
    explicit Form(QWidget *parent = 0);

signals:
    void changeWindow(int from, int to);
    void showMessage(const QString &text, int timeout);

public slots:
};

#endif // FORM_H
