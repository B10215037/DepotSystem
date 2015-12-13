#include "Connector.h"

Connector::Connector() : QNetworkAccessManager() {
    setCookieJar(new QNetworkCookieJar);
}

void Connector::request(QString url, QByteArray jsonData) {
    QUrl qurl(url);
    QNetworkRequest request(qurl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=UTF-8");
    request.setHeader(QNetworkRequest::ContentLengthHeader, jsonData.length());

    QList<QNetworkCookie> cookies = cookieJar()->cookiesForUrl(qurl);
    for(QList<QNetworkCookie>::iterator it = cookies.begin(); it != cookies.end(); ++it)
        request.setHeader(QNetworkRequest::CookieHeader, QVariant::fromValue(*it));

    post(request, jsonData);
}

void Connector::replyFinished(QNetworkReply* reply) {
    reply->deleteLater();

    QString response;

    if (reply->error() != QNetworkReply::NoError) {
        response = reply->errorString();
        qDebug() << "[Connector::replyFinished] @ ERROR]" << response;
        emit sendReceivedMessage(response);
        return;
    }

    if (reply->isReadable()) {
        //Here i check if there is a cookie for me in the reply and extract it
        QList<QNetworkCookie> cookies = qvariant_cast< QList<QNetworkCookie> >(reply->header(QNetworkRequest::SetCookieHeader));
        qDebug() << "[Connector::replyFinished] @ COOKIES]" << cookies;
        //you must tell which cookie goes with which url
        if(cookies.count() != 0) cookieJar()->setCookiesFromUrl(cookies, reply->request().url());

        response = reply->readAll();
        qDebug() << "[Connector::replyFinished @ DATA]" << response;
        QJsonObject jsonObject = QJsonDocument::fromJson(response.toUtf8()).object();
        response = jsonObject.take("message").toString();
        emit sendReceivedMessage(response);
    }
}
