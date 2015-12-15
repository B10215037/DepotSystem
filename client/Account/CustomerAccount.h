#ifndef CUSTOMERACCOUNT_H
#define CUSTOMERACCOUNT_H

#include "Account.h"
#include "../Order/Order.h"

class CustomerAccount : public Account
{
public:
    CustomerAccount(QString id);

    QList<Order> getOrders();
    void addOrder(QList<Item> items);
    void removeOrder(int index);
};

#endif // CUSTOMERACCOUNT_H
