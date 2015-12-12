#include "account.h"

Account::Account(QString id, QString password) : id(id), password(password)
{
}

QList<Order> Account::getOrders() {
    return orders;
}

Order Account::createOrders(QList<Item> items) {
    Order order = new Order(items);
    return order;
}
