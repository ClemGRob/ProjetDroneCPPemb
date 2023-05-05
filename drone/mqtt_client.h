#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <QObject>
#include <QHostAddress>
#include <qmqttclient.h>
#include <qmqttglobal.h>

#define MQTT_VERSION_3_1 QMqttGlobal::MQTTVersion::V3_1

class MQTT_Client : public QObject
{
    Q_OBJECT
public:
    explicit MQTT_Client(QObject *parent =nullptr);

private:
    QMqttClient *m_client;
    QString m_host;
    quint16 m_port;
    QString m_clientId;

signals:
    void messageReceived(const QString &topic, const QByteArray &message);

public slots:
    void onConnected();
    void onDisconnected();
    void onMessageReceived(const QMqttMessage &message);
    void onError(QMqtt::ClientError err);
    void publishMessage(const QString &topic, const QByteArray &message);

};

#endif // MQTT_CLIENT_H
