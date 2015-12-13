#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QtNetwork>
#include <QJsonObject>

class Connector : public QNetworkAccessManager
{
    Q_OBJECT

public:
    Connector();

    void request(QString url, QByteArray jsonData);

signals:
    void sendReceivedMessage(QString response);

public slots:
    void replyFinished(QNetworkReply *reply);
};

#endif // CONNECTOR_H
