#include "mqtt_client.h"

MQTT_Client::MQTT_Client(QObject *parent) : QObject(parent)
{
    m_client = new QMQTTClient(this);
       m_client->setAutoReconnect(true);
       m_client->setCleanSession(true);
       m_client->setClientId("MyMqttClient");
       m_client->setUsername("MyUsername");
       m_client->setPassword("MyPassword");
       m_client->setProtocolVersion(QMQTT::ProtocolVersion::V311);

       m_host = "localhost";
       m_port = 1883;

       connect(m_client, &QMqttClient::connected, this, &MQTT_Client::onConnected);
       connect(m_client, &QMqttClient::disconnected, this, &MQTT_Client::onDisconnected);
       connect(m_client, &QMqttClient::received, this, &MQTT_Client::onMessageReceived);
       connect(m_client, &QMqttClient::error, this, &MQTT_Client::onError);
}

void MQTT_Client::onConnected()
{
    qDebug() << "mqtt://broker.emqx.io:1883" ;
    m_client->subscribe("/ynov/bordeaux/ProjetDroneCPPemb", QOS2);
    publishMessage("/ynov/bordeaux/ProjetDroneCPPemb", "DroneIMG37337.png");
}

void MQTT_Client::onDisconnected()
{
    qDebug() << "Disconnected from broker!";
}

void MQTT_Client::onMessageReceived(const QMqttMessage &message)
{
    qDebug() << "Received message:" << message.topic() << message.payload();
    emit messageReceived(message.topic(), message.payload());
}

void MQTT_Client::onError(QMqtt::ClientError err)
{
    qDebug() << "Error:" << err;
}

void MQTT_Client::publishMessage(const QString &topic, const QByteArray &message)
{
    m_client->publish(topic, message, QOS2);
}
