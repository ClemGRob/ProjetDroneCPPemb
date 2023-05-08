#ifndef BASE_H
#define BASE_H

#include <QObject>
#include <QPixmap>
#include <QDebug>
#include <mosquitto.h>
#include <QImage>
#include"../includes/PAQL.h"

class MQTTImageReceiver : public QObject {
    Q_OBJECT

public:
    MQTTImageReceiver(const std::string& topic);
    ~MQTTImageReceiver();
    static void base64ToImage();
    static QString s_decode_picture();

private:
    std::string s_topic_;
    struct mosquitto* mosq_st;

    static void on_connect(struct mosquitto* mosq, void* obj, int rc);
    static void on_message(struct mosquitto* mosq, void* obj, const struct mosquitto_message* msg);

};


#endif // BASE_H
