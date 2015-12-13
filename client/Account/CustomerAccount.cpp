#include "CustomerAccount.h"

CustomerAccount::CustomerAccount(QString id) : Account(id) {}

QList<Order> CustomerAccount::getOrders() {
    //連線請求
}

void CustomerAccount::addOrder(QList<Item> items) {
    //連線請求
}

void CustomerAccount::removeOrder(int index) {
    //連線請求
}
