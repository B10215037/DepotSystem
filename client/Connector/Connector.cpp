#include "Connector.h"

#define HEADER_DEBUG1

Connector::Connector() : QNetworkAccessManager() {
    setCookieJar(new QNetworkCookieJar);
    serverUrl = "http://140.118.175.208";
}

QByteArray Connector::getLogInFormat(QString username, QString password) {
    return QString("{\"username\":\"%1\", \"password\":\"%2\"}").arg(username, password).toUtf8();
}

///login ---[==========>>>
void Connector::logIn(QByteArray jsonData) {
    post(setRequest("/login", jsonData.size()), jsonData);
}
//login <<<==========]---

///product ---[==========>>>
void Connector::postNewProducts(QByteArray jsonData) {
    post(setRequest("/products", jsonData.size()), jsonData);
}
void Connector::getProductsInfo() {
    get(setRequest("/products", 0));
}
void Connector::putEditedProducts(QByteArray jsonData) {
    put(setRequest("/products", jsonData.length()), jsonData);
}
//products <<<==========]---

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
        qDebug() << "\n[Connector::setRequest @ HEADER]"
                 << headers[i] << request.rawHeader(headers[i]);
#endif

    return request;
}

void Connector::replyFinished(QNetworkReply* reply) {
    reply->deleteLater();

    QString response;

    if (reply->error() != QNetworkReply::NoError) {
        response = reply->errorString() + reply->readAll();
        qDebug() << "\n[Connector::replyFinished] @ ERROR]" << response;
        emit sendReceivedMessage(response);
        return;
    }

    if (reply->isReadable()) {
        QList<QNetworkCookie> cookies =
                qvariant_cast< QList<QNetworkCookie> >(reply->header(QNetworkRequest::SetCookieHeader));
        qDebug() << "\n[Connector::replyFinished] @ COOKIES]" << cookies;

        if(cookies.count() != 0) cookieJar()->setCookiesFromUrl(cookies, reply->request().url());

        response = reply->readAll();
        qDebug() << "\n[Connector::replyFinished @ DATA]" << response;

//        QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
//        if (jsonDoc.isObject()) {
//            response = jsonDoc.object()["message"].toString();
//        }
//        else if (jsonDoc.isArray()) {
//            response = jsonDoc.array().size();
//        }

        emit sendReceivedMessage(response);
    }
}
