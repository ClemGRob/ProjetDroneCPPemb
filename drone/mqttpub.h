#ifndef BASE_H
#define BASE_H

#include <QPixmap>
#include <QDebug>
#include <mosquitto.h>
#include"../includes/PAQL.h"


class MQTTImageReceiver{

public:
    MQTTImageReceiver(const string& topic);
    ~MQTTImageReceiver();
    void pub(string msg);


private:
    string topic_;
    struct mosquitto* mosq_;

    static void on_connect(struct mosquitto* mosq, void* obj, int rc);
    static void on_message(struct mosquitto* mosq, void* obj, const struct mosquitto_message* msg);
};


#endif // BASE_H
