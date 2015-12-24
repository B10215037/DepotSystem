#ifndef MANAGERACCOUNT_H
#define MANAGERACCOUNT_H

#include <QList>
#include "Account.h"
#include "../Order/Order.h"

class ManagerAccount : public Account
{
public:
    ManagerAccount();

    QList<Product> newProducts, deletedProducts, changedProducts;
};

#endif // MANAGERACCOUNT_H
