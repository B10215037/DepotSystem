#include "product.h"

Product::Product()
{
    name = "";
    stock = 0;
    price = 0;
}

Product::Product(QString id) : ID(id)
{
	name = "";
	stock = 0;
	price = 0;
}

QString Product::getName()
{
	return name;
}

void Product::setName(QString name)
{
	this->name = name;
}

int Product::getStock()
{
	return stock;
}

void Product::setStock(int amount)
{
	this->stock = amount;
}

int Product::getPrice()
{
	return price;
}

void Product::setPrice(int price)
{
    this->price = price;
}

QString Product::getID()
{
	return ID;
}

bool Product::hasID() {
    return !(ID.isNull() || ID.isEmpty());
}

QString Product::toJson() {
    if (hasID())
        return QString("{\"id\":\"%1\",\"productname\":\"%2\",\"stock\":%3,\"price\":%4}")
                .arg(ID).arg(name).arg(stock).arg(price);
    return QString("{\"productname\":\"%2\",\"stock\":%3,\"price\":%4}")
            .arg(name).arg(stock).arg(price);
}
