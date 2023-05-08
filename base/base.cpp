#include "base.h"
#include "mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QFile>
#include <QPixmap>
#include <QWidget>
//QImage imgtoc= new QImage();
int cpt = 0;
char img1[60000] = "";

MQTTImageReceiver::MQTTImageReceiver(const std::string& topic) : topic_(topic) {
    const char* ADDRESS = "broker.emqx.io";

    const int PORT = 1883;
    const int KEEP_ALIVE = 200;

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

void MQTTImageReceiver::on_connect(struct mosquitto* mosq, void* obj, int rc) {
    if (rc != 0) {
        qDebug() << "Error connecting to Mosquitto: " << rc;
    }
}

void MQTTImageReceiver::on_message(struct mosquitto* mosq, void* obj, const struct mosquitto_message* msg) {
    // m_imageData = std::vector<unsigned char>(static_cast<const unsigned char*>(msg->payload), static_cast<const unsigned char*>(msg->payload) + msg->payloadlen);
    
    // if (std::string(static_cast<const char*>(msg->payload), msg->payloadlen) == "FIN") {
    //         // Appeler la fonction fin()
    //         base64ToImage();
    //         return;
    //     }
    if (std::string(static_cast<const char*>(msg->payload), msg->payloadlen) == "FIN")base64ToImage();
    // else{
    //     QByteArray bytes = QByteArray::fromBase64(static_cast<const char*>(msg->payload));

    // // Ajouter les données d'octets à l'image existante
    // //globalImage.loadFromData(bytes);
    // }
    strcat(img1, static_cast<const char*>(msg->payload));
    // if(cpt<3)strcat(img1, static_cast<const char*>(msg->payload));
    // else if(cpt<6)strcat(img2, static_cast<const char*>(msg->payload));
    // else if(cpt<9)strcat(img3, static_cast<const char*>(msg->payload));
    // else if(cpt<12)strcat(img4, static_cast<const char*>(msg->payload));
    
    cpt +=1;
    
    printf("%s\n",msg->payload);
    printf("\n%d\n", cpt);
    // QByteArray messageArray((const char*)msg->payload, msg->payloadlen);
    // printf("%s",msg->payload);

    // Convertir le QByteArray en QImage
    // QByteArray imageData = QByteArray::fromBase64(messageArray);
    // QImage image = QImage::fromData(imageData, "PNG");
    // image.save("../ok.png");
    // QByteArray imageData(static_cast<char*>(msg->payload), msg->payloadlen);
    // QPixmap pixmap;
    // pixmap.loadFromData(imageData);
    // pixmap.save("../image.jpg", "JPG");
    
    // float64_t lat, lon;
    // receiver->findHiddenCoordinates(imageData, lat, lon);

    // emit receiver->imageReceived(pixmap, lat, lon);
}



void MQTTImageReceiver::base64ToImage()
{
    printf("\n%s\nok\n",img1);
    // QByteArray imageDataBytes(reinterpret_cast<const char*>(imageData.data()), imageData.size());
    // QByteArray imageDataBytesDecoded = QByteArray::fromBase64(imageDataBytes);

    // QImage image;
    // if (image.loadFromData(reinterpret_cast<const uchar*>(imageDataBytesDecoded.data()), imageDataBytesDecoded.size())) {
    //     image.save("../save.png");
    // }
}
