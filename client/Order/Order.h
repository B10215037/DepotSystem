#ifndef Order_H
#define Order_H

#include <QString>
#include "../Product/Product.h"
#include <QList>

typedef QString ProductID;

struct Item
{
    ProductID product;
	int amount;

    Item(ProductID p, int num): product(p), amount(num){
    }
    Item(){
    }

    QString toJson() {
    	if(amount == 0){
    		return QString("{\"productId\":\"%1\",\"amount\":\"%2\",\"cancelled\":\"true\"}")
                .arg(product).arg(amount);
    	}
        return QString("{\"productId\":\"%1\",\"amount\":\"%2\"}")
                .arg(product).arg(amount);
        
    }
};

class Order
{
public:
	Order();
	Order(QString);
	QString getNumber();
    QString getState();
    void setState(QString);
    QList<Item> getItems();
	void addItem(QString, int);
	int getItemAmount(QString);
	void setItemAmount(QString, int);
	void deleteItem(QString);
	void submit();
	bool isSubmitted();
	void setSubmitted(bool);
	QString getWhoOrdered();
	void setWhoOrdered(QString);
	QString getWhoTaken();
	void setWhoTaken(QString);

	QString toJson();

private:
    QString number;
    QString state;
	QList<Item> items;
	bool submitted;
	QString orderedBy;
	QString takenBy;

};

#endif // PRODUCT_H
