#include "Order.h"

Order::Order() {
}

Order::Order(QString id):number(id){
}

Product getProductWithID(ProductID id){
	Product p;
	
	return p;
}

QString Order::getNumber(){
	return number;
}


QString Order::getState(){
	return state;
}

void Order::setState(QString stateParam){
    state = stateParam;
}

QList<Item> Order::getItems(){
	return items;
}

void Order::addItem(QString name, int amount = 1){

    items.append(Item(name, amount));

}

int Order::getItemAmount(QString name){
	int i = 0, itemSize = items.size();
	while(i < itemSize){
        if(getProductWithID(items[i].product).getName() == name){
			return items[i].amount;
		}
		i++;
	}
	return -1;
}

void Order::setItemAmount(QString name, int amount){
	int i = 0, itemSize = items.size();
	while(i < itemSize){
        if(items[i].product == name){
			items[i].amount = amount;
			break;
		}
		i++;
	}
}

void Order::deleteItem(QString name){
// 	QVectorIterator<Item> iter(items);
// 	while (iter.hasNext()){
// 		Item tmpItem = iter.next();
//         if(getProductWithID(tmpItem.product).getName() == name){
// //            items.erase(iter.previous()); TODO
// 			break;
// 		}
// 	}
}

void Order::submit(){

}

bool Order::isSubmitted(){
    return submitted; //TODO
}

void Order::setSubmitted(bool param){
	submitted = param;
}

QString Order::getWhoOrdered(){
	return orderedBy;
}

void Order::setWhoOrdered(QString id){
	orderedBy = id;
}

QString Order::getWhoTaken(){
	return takenBy;
}

void Order::setWhoTaken(QString id){
	takenBy = id;
}
