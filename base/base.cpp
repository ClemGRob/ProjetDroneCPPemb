#include "base.h"
#include "mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QFile>
#include <QPixmap>
#include <QWidget>
#include <QBitArray>
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
    if (std::string(static_cast<const char*>(msg->payload), msg->payloadlen) == "FIN")base64ToImage();
    else {strcat(img1, static_cast<const char*>(msg->payload));
    }
}



void MQTTImageReceiver::base64ToImage()
{
    QByteArray imageData = QByteArray::fromBase64(img1);
    QImage i_image = QImage::fromData(imageData);
    i_image.save("../save.png");
    
    // Vérifier si la conversion a réussi
    if (i_image.isNull()) {
        qWarning() << "Impossible de charger l'image à partir des données Base64.";
    }

    qWarning() <<"Le message secret est : "<<decode_picture()<<endl<<"cet affichage disparetra après l'implémentation de l'IHM";

}
QString MQTTImageReceiver::decode_picture()
{
    QImage i_image("../save.png");
    unsigned char *pixels = i_image.bits();
    int imageSize = i_image.width() * i_image.height();

    QBitArray messageBits(imageSize/8);  
    for (int i = 0; i < messageBits.size(); i++) {
        unsigned char pixel = pixels[i];
        bool bit = (pixel & 1) != 0;
        messageBits.setBit(i,bit);
    }

    QByteArray messageData;
    int numBits = messageBits.size();
    for (int i = 0; i < numBits/8; i += 1) {
        char byte = 0;
        for (int j = 0; j < 8; j++) {
            byte |= (messageBits.testBit(i*8+j) << 7-j);
            
        }
        if(byte =='\t')break;
        messageData.append(byte);
    }
    QString message = QString(messageData.constData());
    qWarning() << message;
    return message;
}
 