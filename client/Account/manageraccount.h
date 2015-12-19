#ifndef MANAGERACCOUNT_H
#define MANAGERACCOUNT_H

#include <QList>
#include "Account.h"
#include "../Order/Order.h"

class ManagerAccount : public Account
{
public:
    ManagerAccount(QString id);

//    QList<Order> getOrdersWereTaken();
//    QList<Order> getOrdersWillBeTaken();
//    void acceptOrder(int index);
//    void rejectOrder(int index);

//private:
//    Order ordersWereTaken, ordersWillBeTaken;
};

#endif // MANAGERACCOUNT_H
