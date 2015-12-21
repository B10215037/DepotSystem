#include "Connector.h"

#define HEADER_DEBUG

Connector::Connector() : QNetworkAccessManager() {
//    setCookieJar(new QNetworkCookieJar);
    serverUrl = "http://140.118.175.208";

//    connect(this, SIGNAL(finished(QNetworkReply*)),
//            this, SLOT(replyFinished(QNetworkReply*)));
}

///register
void Connector::registerAccount(QString userName, QString password) {
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
    clearAccessCache();
    QList<QNetworkCookie> cookies = cookieJar()->cookiesForUrl(QUrl(serverUrl + "/login"));
    for (int i = 0; i < cookies.size(); i++)
        cookieJar()->deleteCookie(cookies[i]);
    get(QNetworkRequest(QUrl(serverUrl + "/logout")));
}

///product
void Connector::postNewProducts(Product *products, int size) {
    QByteArray jsonData = "[";
    for (int i = 0; i < size; i++)
        if (i == size - 1) jsonData += products[i].toJson();
        else jsonData += products[i].toJson() + ",";
    jsonData += "]";
    qDebug() << "@@@" << jsonData;
    post(setRequest("/products", jsonData.size()), jsonData);
}

void Connector::getProductsInfo() {
    get(QNetworkRequest(QUrl(serverUrl + "/products")));
}

void Connector::putEditedProducts(Product *products, int size) {
    QByteArray jsonData = "[";
    for (int i = 0; i < size; i++)
        if (i == size - 1) jsonData += products[i].toJson();
        else jsonData += products[i].toJson() + ",";
    jsonData += "]";
    qDebug() << "###" << jsonData;
    put(setRequest("/products", jsonData.size()), jsonData);
}

///Order
void Connector::postNewOrders(State s, QVector<Item> items){
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

void Connector::getOrdersInfo() {
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

//void Connector::replyFinished(QNetworkReply* reply) {
//    reply->deleteLater();

//    QString response;

//    if (reply->error() != QNetworkReply::NoError) {
//        response = reply->errorString() + reply->readAll();
//        qDebug() << "\n[UserView::replyFinished] @ ERROR]" << response;
//        emit sendReceivedMessage(response);
//        return;
//    }

//    if (reply->isReadable()) {
//        QList<QNetworkCookie> cookies =
//                qvariant_cast< QList<QNetworkCookie> >(reply->header(QNetworkRequest::SetCookieHeader));
//        qDebug() << "\n[UserView::replyFinished] @ COOKIES]" << cookies;

//        if(cookies.count() != 0) cookieJar()->setCookiesFromUrl(cookies, reply->request().url());

//        response = reply->readAll();
//        printf("\n[UserView::replyFinished @ DATA] %s\n", response.toUtf8().data());
//        fflush(stdout);
//        emit sendReceivedMessage(response);
//    }
//}
