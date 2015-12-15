#include "product.h"

Product::Product()
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

int Product::getID()
{
	return ID;
}
