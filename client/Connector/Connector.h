#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QtNetwork>
#include <QJsonObject>

class Connector : public QNetworkAccessManager
{
    Q_OBJECT

public:
    Connector();

    QByteArray getLogInFormat(QString username, QString password);

    ///login
    void logIn(QByteArray jsonData);

    ///products
    void postNewProducts(QByteArray jsonData);
    void getProductsInfo();
    void putEditedProducts(QByteArray jsonData);

private:
    QString serverUrl;

    QNetworkRequest setRequest(QString path, int dataSize);

signals:
    void sendReceivedMessage(QString response);

public slots:
    void replyFinished(QNetworkReply *reply);
};

#endif // CONNECTOR_H
