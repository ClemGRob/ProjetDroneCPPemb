#include <QCoreApplication>
#include "mqtt_client.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MqttClient client;

    QObject::connect(&client, &MqttClient::messageReceived, [](const QString &topic, const QByteArray &message) {
        qDebug() << "Received message:" << topic << message;
    });

    client.connectToHost();

    return a.exec();
}
