#ifndef Order_H
#define Order_H

#include <QString>
#include <QVector>
#include "../Product/Product.h"

typedef QString ProductID;

enum State{Archived, Submitted, Processing, Shipping, Arrived};
struct Item
{
    ProductID product;
	int amount;

    Item(ProductID p, int num): product(p), amount(num){

    }
    Item(){

    }

    QString toJson() {

        return QString("{\"id\":\"%1\",\"amount\":%2}")
                .arg(product).arg(amount);
        
    }
};

class Order
{
public:
	Order();
	int getNumber();
	State getState();
	void setState(State);
	QVector<Item> getItems();
	void addItem(QString, int);
	int getItemAmount(QString);
	void setItemAmount(QString, int);
	void deleteItem(QString);
	void submit();
	bool isSubmitted();
	QString getWhoOrdered();
	void setWhoOrdered(QString);
	QString getWhoTaken();
	void setWhoTaken(QString);

	QString toJson();

private:
	int number;
	State state;
	QVector<Item> items;
	bool submitted;
	QString orderedBy;
	QString takenBy;

};

#endif // PRODUCT_H
