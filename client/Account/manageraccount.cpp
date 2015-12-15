#include "manageraccount.h"

ManagerAccount::ManagerAccount(QString id) : Account(id) {}

QList<Order> ManagerAccount::getOrdersWereTaken() {
    //連線請求
	return QList<Order>();//TODO
}

QList<Order> ManagerAccount::getOrdersWillBeTaken() {
    //連線請求
	return QList<Order>();//TODO
}

void ManagerAccount::acceptOrder(int index) {
    //連線請求
}

void ManagerAccount::rejectOrder(int index) {
    //連線請求
}
