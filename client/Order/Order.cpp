#include "Order.h"

const QString Order::stateText[5] = {"Archived", "Submitted", "Processing", "Shipping", "Arrived"};

// Order getOrder(int num){
// 	Order tmp;

// 	/*access order database*/

// 	//tmp = OrderDataBaseManager::find(num);

// 	return tmp;
// }

// Order getAllOrders(){

// }
Order::Order() {

}

Order::Order(QString id):number(id){

}

Product getProductWithID(ProductID id){
	Product p;
/*	Getting Product*/
	return p;
}

QString Order::getNumber(){
	return number;
}


State Order::getState(){
	return state;
}

void Order::setState(int stateParam){
    state = (State)stateParam;
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
