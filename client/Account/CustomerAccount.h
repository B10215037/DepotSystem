#ifndef CUSTOMERACCOUNT_H
#define CUSTOMERACCOUNT_H

#include <QList>
#include "Account.h"
#include "../Order/Order.h"

class CustomerAccount : public Account
{
public:
    CustomerAccount(QString id);

//    QList<Order> getOrders(); //local temp
//    void orderNewOrder(Order item); //下訂單 local change -> server update
//    void cancelOrDeleteOrder(int index); //取消或刪除訂單 local change -> server update

//private:
//    QList<Order> orders; //local temp
};

#endif // CUSTOMERACCOUNT_H
