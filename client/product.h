#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product
{
public:
	Product();
	QString getName();
	void setName(QString name);
	int getStock();
	void setStock(int amount);
	int getPrice();
	void setPrice(int price);

private:
	QString name;
	int stock;
	int price;

};

#endif // PRODUCT_H
