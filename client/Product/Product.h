#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product
{
public:
    Product();
    Product(QString id);
    QString getName();
    void setName(QString name);
    int getStock();
    void setStock(int amount);
    int getPrice();
    void setPrice(int price);
    QString getID();
    bool hasID();
    QString toJson();

private:
    QString name;
    int stock;
    int price;
    QString ID;

};

#endif // PRODUCT_H
