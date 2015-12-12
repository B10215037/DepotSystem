#ifndef MANAGERACCOUNT_H
#define MANAGERACCOUNT_H

#include "account.h"

class ManagerAccount : public Account
{
public:


    ManagerAccount();

    QList<Order> getOrdersTaken();
    Order takeOrder(int number);
    takeOrders(QList<int> numberList);
};

#endif // MANAGERACCOUNT_H
