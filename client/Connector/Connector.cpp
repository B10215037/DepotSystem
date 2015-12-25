#include "Connector.h"

#define HEADER_DEBUG

Connector::Connector() : QNetworkAccessManager() {
#define url_a "http://depot-system.herokuapp.com";
#define url_b "http://140.118.175.208";
    serverUrl = url_a;
}

///register
void Connector::registerAccount(QString userName, QString password) { //待測
    QString jsonData = QString("{\"username\":\"%1\",\"password\":\"%2\"}").arg(userName, password);
    post(setRequest("/register", jsonData.size()), jsonData.toUtf8());
}

///login
void Connector::logIn(QString username, QString password) {
    QString jsonData = QString("{\"username\":\"%1\",\"password\":\"%2\"}").arg(username, password);
    post(setRequest("/login", jsonData.size()), jsonData.toUtf8());
}

///logout
void Connector::logOut() {
    get(setRequest("/logout", 0));

    clearAccessCache();
    QList<QNetworkCookie> cookies = cookieJar()->cookiesForUrl(QUrl(serverUrl + "/login"));
    for (int i = 0; i < cookies.size(); i++)
        cookieJar()->deleteCookie(cookies[i]);
}

///product
void Connector::postNewProducts(Product *products, int size) {
    QByteArray jsonData = "[";
    for (int i = 0; i < size; i++)
        if (i == size - 1) jsonData += products[i].toJson();
        else jsonData += products[i].toJson() + ",";
    jsonData += "]";
    post(setRequest("/products", jsonData.size()), jsonData);
}

void Connector::postNewProducts(QList<Product> products) {
    QByteArray jsonData = "[";
    for (int i = 0; i < products.size(); i++)
        if (i == products.size() - 1) jsonData += products[i].toJson();
        else jsonData += products[i].toJson() + ",";
    jsonData += "]";
    post(setRequest("/products", jsonData.size()), jsonData);
}

void Connector::getProductsInfo() {
    get(QNetworkRequest(QUrl(serverUrl + "/products")));
}

void Connector::putEditedProducts(Product *products, int size) { //待測
    QByteArray jsonData = "[";
    for (int i = 0; i < size; i++)
        if (i == size - 1) jsonData += products[i].toJson();
        else jsonData += products[i].toJson() + ",";
    jsonData += "]";
    put(setRequest("/products", jsonData.size()), jsonData);
}

void Connector::putEditedProducts(QList<Product> products) { //待測
    QByteArray jsonData = "[";
    for (int i = 0; i < products.size(); i++)
        if (i == products.size() - 1) jsonData += products[i].toJson();
        else jsonData += products[i].toJson() + ",";
    jsonData += "]";
    put(setRequest("/products", jsonData.size()), jsonData);
}

void Connector::deleteProducts(QList<Product> products) { //待測
    QByteArray jsonData = "[";
    for (int i = 0; i < products.size(); i++)
        if (i == products.size() - 1)
            jsonData += QString("{\"id\":\"%1\"}").arg(products[i].getID());
        else jsonData += QString("{\"id\":\"%1\"}").arg(products[i].getID()) + ",";
    jsonData += "]";
    deleteResource(setRequest("/products", jsonData.size()));
}

///Order
void Connector::postNewOrders(State s, QVector<Item> items){ //待測
    int size = items.size();
    //Adding state
    QByteArray jsonData = "";
    jsonData += QString("{\"state\":%1,\"items\":").arg(s);

    //Adding items
    jsonData += "[";
    for (int i = 0; i < size; i++)
        if (i == size - 1) jsonData += items[i].toJson();
        else jsonData += items[i].toJson() + ",";
    jsonData += "]}";
    qDebug() << "@@@" << jsonData;
    post(setRequest("/userOrders", jsonData.size()), jsonData);
}

void Connector::getOrdersInfo() { //待測
    get(QNetworkRequest(QUrl(serverUrl + "/userOrders")));
}

QNetworkRequest Connector::setRequest(QString path, int dataSize) {
    QUrl qurl(serverUrl + path);
    QNetworkRequest request(qurl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=UTF-8");
    request.setHeader(QNetworkRequest::ContentLengthHeader, dataSize);

    QList<QNetworkCookie> cookies = cookieJar()->cookiesForUrl(qurl);
    for(int i = 0; i < cookies.size(); i++)
        request.setHeader(QNetworkRequest::CookieHeader, QVariant::fromValue(cookies[i]));

#ifdef HEADER_DEBUG
    QList<QByteArray> headers = request.rawHeaderList();
    for (int i = 0; i < headers.size(); i++)
        printf("\n[Connector::setRequest @ HEADER] %s %s\n",
               headers[i].data(), request.rawHeader(headers[i]).data());
    fflush(stdout);
#endif

    return request;
}
