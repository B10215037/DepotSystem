#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>

class Account
{
protected:
    QString id;

public:
    Account(QString id);
    QString getId();
};

#endif // ACCOUNT_H
