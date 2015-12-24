#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>

class Account
{
protected:
    QString id;

public:
    Account();
    void setId(QString ID);
    QString getId();
};

#endif // ACCOUNT_H
