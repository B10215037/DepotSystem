#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QtNetwork>
#include <QJsonObject>
#include "../Product/Product.h"

class Connector : public QNetworkAccessManager
{
    Q_OBJECT

public:
    Connector();

    ///register
    void registerAccount(QString userName, QString password);

    ///login
    void logIn(QString userName, QString password);

    ///logout
    void logOut();

    ///products
    void postNewProducts(Product *products, int size);
    void getProductsInfo();
    void putEditedProducts(Product *products, int size);

private:
    QString serverUrl;

    QNetworkRequest setRequest(QString path, int dataSize);

signals:
    void sendReceivedMessage(QString response);

public slots:
    void replyFinished(QNetworkReply *reply);
};

#endif // CONNECTOR_H
