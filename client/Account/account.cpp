#include "Account.h"

Account::Account(QString id) : id(id) {}

QString Account::getId() {
    return id;
}
