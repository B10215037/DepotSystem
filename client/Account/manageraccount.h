#ifndef MANAGERACCOUNT_H
#define MANAGERACCOUNT_H

#include "account.h"

class ManagerAccount : public Account
{
private:
    QList<Order> ordersTaken;
public:
    ManagerAccount(QString id, QString password);
    QList<Order> getOrdersTaken();
    Order takeOrder(int number);
    QList<Order> takeOrders(QList<int> numberList);
};

#endif // MANAGERACCOUNT_H
