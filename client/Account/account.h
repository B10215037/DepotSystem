#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QVector>

class Account
{
public:
    QString id, password;
    QList<Order> orders;

    Account(QString id, QString password);
    Order getOrders();
    Order createOrders(QList<Item> items);
};

#endif // ACCOUNT_H
