#include "mqttpub.h"

MQTTImageReceiver::MQTTImageReceiver(const string& topic) : topic_(topic) {
    const char* ADDRESS = "broker.emqx.io";
    const int PORT = 1883;
    const int KEEP_ALIVE = 60;

    mosquitto_lib_init();
    mosq_ = mosquitto_new(NULL, true, this);

    if (!mosq_) {
        qDebug() << "Error initializing Mosquitto";
        return;
    }

    mosquitto_connect_callback_set(mosq_, on_connect);
    mosquitto_message_callback_set(mosq_, on_message);

    int ret = mosquitto_connect(mosq_, ADDRESS, PORT, KEEP_ALIVE);
    if (ret != MOSQ_ERR_SUCCESS) {
        qDebug() << "Error connecting to Mosquitto";
        return;
    }

    ret = mosquitto_subscribe(mosq_, NULL, topic.c_str(), 2);
    if (ret != MOSQ_ERR_SUCCESS) {
        qDebug() << "Error subscribing to Mosquitto topic";
        return;
    }

    ret = mosquitto_loop_start(mosq_);
    if (ret != MOSQ_ERR_SUCCESS) {
        qDebug() << "Error starting Mosquitto loop";
        return;
    }
}

MQTTImageReceiver::~MQTTImageReceiver() {
    if (mosq_) {
        mosquitto_loop_stop(mosq_, true);
        mosquitto_disconnect(mosq_);
        mosquitto_destroy(mosq_);
    }
    mosquitto_lib_cleanup();
}


void MQTTImageReceiver::pub(string msg)
{
    printf("%s",this->topic_.c_str());
    mosquitto_publish(mosq_, NULL, this->topic_.c_str(), strlen(msg.c_str()), msg.c_str(), 0, false);
    mosquitto_publish(mosq_, NULL, this->topic_.c_str(), strlen(msg.c_str()), msg.c_str(), 1, false);
    mosquitto_publish(mosq_, NULL, this->topic_.c_str(), strlen(msg.c_str()), msg.c_str(), 2, false);
    printf("ok sent\n");
}

void MQTTImageReceiver::on_connect(struct mosquitto* mosq, void* obj, int rc) {
    if (rc != 0) {
        qDebug() << "Error connecting to Mosquitto: " << rc;
    }
}

void MQTTImageReceiver::on_message(struct mosquitto* mosq, void* obj, const struct mosquitto_message* msg) {
    MQTTImageReceiver* receiver = static_cast<MQTTImageReceiver*>(obj);
    QByteArray imageData(static_cast<char*>(msg->payload), msg->payloadlen);
    QPixmap pixmap;
    pixmap.loadFromData(imageData);
    
}