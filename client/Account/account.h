#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QVector>

class Account // == CustomerAccount
{
protected:
    QString id, password;
    QList<Order> orders;

public:
    Account(QString id, QString password);
    QList<Order> getOrders();
    Order createOrders(QList<Item> items);
};

#endif // ACCOUNT_H
