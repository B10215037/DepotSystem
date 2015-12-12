#include "manageraccount.h"

ManagerAccount::ManagerAccount(QString id, QString password) : id(id), password(password)
{
}

QList<Order> ManagerAccount::getOrdersTaken() {
    return ordersTaken;
}

Order ManagerAccount::takeOrder(int number) {
    return ordersTaken[number];
}

QList<Order> ManagerAccount::takeOrders(QList<int> numberList) {
    QList<Order> someOrders = new QList<Order>;
    for (int i = 0; i < numberList.size(); i++)
        someOrders.append(ordersTaken[numberList[i]]);
    return someOrders;
}
