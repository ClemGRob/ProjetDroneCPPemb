#include "base.h"
#include "mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QFile>
#include <QPixmap>
#include <QWidget>
#include <QBitArray>

char c_image_b_64[60000] = "";

MQTTImageReceiver::MQTTImageReceiver(const std::string& s_topic) : s_topic_(s_topic) 
{
    const char* c_ADDRESS_ptr = "broker.emqx.io";

    const int s32_PORT = 1883;
    const int s32_KEEP_ALIVE = 200;

    mosquitto_lib_init();
    mosq_st = mosquitto_new(NULL, true, this);

    if (!mosq_st) 
    {
        qDebug() << "Error initializing Mosquitto";
        return;
    }

    mosquitto_connect_callback_set(mosq_st, on_connect);
    mosquitto_message_callback_set(mosq_st, on_message);

    int s32_ret = mosquitto_connect(mosq_st, c_ADDRESS_ptr, s32_PORT, s32_KEEP_ALIVE);
    if (s32_ret != MOSQ_ERR_SUCCESS) 
    {
        qDebug() << "Error connecting to Mosquitto";
        return;
    }

    s32_ret = mosquitto_subscribe(mosq_st, NULL, s_topic.c_str(), 2);
    if (s32_ret != MOSQ_ERR_SUCCESS) 
    {
        qDebug() << "Error subscribing to Mosquitto s_topic";
        return;
    }

    s32_ret = mosquitto_loop_start(mosq_st);
    if (s32_ret != MOSQ_ERR_SUCCESS) 
    {
        qDebug() << "Error starting Mosquitto loop";
        return;
    }
}

MQTTImageReceiver::~MQTTImageReceiver() {
    if (mosq_st) 
    {
        mosquitto_loop_stop(mosq_st, true);
        mosquitto_disconnect(mosq_st);
        mosquitto_destroy(mosq_st);
    }
    mosquitto_lib_cleanup();
}

void MQTTImageReceiver::on_connect(struct mosquitto* mosq_st, void* obj, int s32_rc) {
    if (s32_rc != 0) 
    {
        qDebug() << "Error connecting to Mosquitto: " << s32_rc;
    }
}

void MQTTImageReceiver::on_message(struct mosquitto* mosq_st, void* obj, const struct mosquitto_message* msg_s) {
    if (std::string(static_cast<const char*>(msg_s->payload), msg_s->payloadlen) == "FIN")base64ToImage();
    else 
    {
        strcat(c_image_b_64, static_cast<const char*>(msg_s->payload));
    }
}



void MQTTImageReceiver::base64ToImage()
{
    QByteArray Q_imageData = QByteArray::fromBase64(c_image_b_64);
    QImage i_image = QImage::fromData(Q_imageData);
    i_image.save("../save.png");
    if (i_image.isNull()) 
    {
        qWarning() << "Impossible de charger l'image à partir des données Base64.";
    }

    qWarning() <<"Le message secret est : "<<s_decode_picture()<<endl<<"cet affichage disparaitra après l'implémentation de l'IHM";

}
QString MQTTImageReceiver::s_decode_picture()
{
    QImage i_image("../save.png");
    unsigned char *c_pixels = i_image.bits();
    int s32_imageSize = i_image.width() * i_image.height();

    QBitArray messageBits_tab(s32_imageSize/8);  
    for (int i = 0; i < messageBits_tab.size(); i++) 
    {
        unsigned char pixel = c_pixels[i];
        bool bit = (pixel & 1) != 0;
        messageBits_tab.setBit(i,bit);
    }

    QByteArray messageData_tab;
    int numBits = messageBits_tab.size();
    for (int i = 0; i < numBits/8; i += 1) 
    {
        char c_byte = 0;
        for (int j = 0; j < 8; j++) 
        {
            c_byte |= (messageBits_tab.testBit(i*8+j) << 7-j);    
        }
        if(c_byte =='\t')break;
        messageData_tab.append(c_byte);
    }
    QString s_message = QString(messageData_tab.constData());
    qWarning() << s_message;
    return s_message;
}
 