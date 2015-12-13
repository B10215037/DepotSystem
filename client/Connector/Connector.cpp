#include "Connector.h"

Connector::Connector() : QNetworkAccessManager() {}

void Connector::request(QString url, QByteArray requestData) {
    QUrl qurl(url);
    QNetworkRequest request(qurl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=UTF-8");
    request.setHeader(QNetworkRequest::ContentLengthHeader, requestData.length());
    post(request, requestData);
}

void Connector::replyFinished(QNetworkReply* reply) {
    QString response;
    if (reply->isReadable()) {
        QString strReply = reply->readAll();
        qDebug() << "[Connector::replyFinished] DATA: " << strReply;

        QJsonObject jsonObject = QJsonDocument::fromJson(strReply.toUtf8()).object();
        response = jsonObject.take("message").toString();
        qDebug() << response;
        emit sendReceivedMessage(response);
    }
    else {
        response = reply->errorString();
        qDebug() << "[Connector::replyFinished] ERROR: " << response;
        emit sendReceivedMessage(response);
    }

    reply->deleteLater();
}
