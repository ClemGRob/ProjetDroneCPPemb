#include "pictureencoder.h"
#include <QString>
#include <bitset>
#include <iostream>
#include <QByteArray>
#include <QtCore/QBitArray>
#include<mosquitto.h>
#include<QBuffer>
#include <chrono>
#include <thread>
#include<QCoreApplication>
#include<QTime>
PictureEncoder::PictureEncoder(QString s_image_name,QString s_data)
{
    this->s_image_name = s_image_name;
    this->s_data = s_data + QString("\t");
    this->b_data_tab = this->s_data.toStdString().c_str();//.toUtf8();


}


void PictureEncoder::encode_data()
{}

void PictureEncoder::encode_picture()
{
    this->i_image = QImage(this->s_image_name);
    unsigned char *pixels = this->i_image.bits();
    int pixel_cmp = 0;
    for (int i = 0; i < this->s_data.length(); i++) {
        //chaque caractere
        QByteArray utf8 = this->s_data.mid(i, 1).toUtf8();
        const char* data = utf8.data();
        for (int j = 0; j < utf8.length(); j++) {
            //chaque bit
            unsigned char byte = data[j];
            for (int k = 7; k >= 0; k--) {
                //chaque pixel
                if(((byte >> k) & 1)==1)
                    pixels[pixel_cmp]|= 0x01;
                else
                    pixels[pixel_cmp]&= 0xFE;
                pixel_cmp+=1;
                
            }
        }
    }


}

QString PictureEncoder::decode_picture()
{
unsigned char *pixels = this->i_image.bits();
    int imageSize = this->i_image.width() * this->i_image.height();

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
    return message;
}
    

void PictureEncoder::make_sendable()
{
    // QImage image("mon_image.png");

    // Convertir l'image en base64
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    this->i_image.save(&buffer, "PNG");
    QString base64 = byteArray.toBase64();
    //char* ttt= base64.toStdString().c_str();
    printf("Contenu base64 : %s", base64.toStdString().c_str());


    struct mosquitto *mosq = mosquitto_new(NULL, true, NULL);
    mosquitto_connect(mosq, "broker.emqx.io", 1883, 60);


    int num_chunks = base64.length() / 100;
    if (base64.length() % 100 != 0)
    {
        num_chunks++;
    }
    for (int i = 0; i < num_chunks; i++)
    {
        int chunk_start = i * 100;
        int chunk_length = min((int)base64.length() - chunk_start, 100);
        string chunk = base64.mid(chunk_start, chunk_length).toStdString();
        printf("%s\n",chunk.c_str());

        // Publier le message sur un topic MQTT
        mosquitto_publish(mosq, NULL, "/ynov/bordeaux/ProjetDroneCCPPemb", chunk_length, chunk.c_str(), 0, false);
        QTime dieTime= QTime::currentTime().addMSecs(1);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    }
// int num_chunks = base64.length() / 10;
//     if (base64.length() % 10 != 0)
//     {
//         num_chunks++;
//     }
//     for (int i = 0; i < num_chunks; i++)
//     {
//         int chunk_start = i * 10;
//         int chunk_length = std::min(base64.length() - chunk_start, 10);
//         QString chunk = base64.mid(chunk_start, chunk_length);

//         // Publier le message sur un topic MQTT
//         mosquitto_publish(client, NULL, topic.toUtf8().constData(), chunk_length, chunk.toUtf8().constData(), 0, false);
//     }


    // mosquitto_publish(client, NULL, "mon_topic", base64.length(), base64.toStdString().c_str(), 0, false);
    // mosquitto_publish(mosq, NULL, "/ynov/bordeaux/ProjetDroneCCPPemb", base64.length(), base64.toStdString().c_str(), 2, false);


    // //cout<<byteArray;
    // // mosquitto_publish(mosq, NULL, "/ynov/bordeaux/ProjetDroneCCPPemb", strlen(base64.toStdString().c_str()), base64.toStdString().c_str(), 2, false);
    // mosquitto_publish(mosq, NULL, "/ynov/bordeaux/ProjetDroneCCPPemb", 3, "aaa", 2, false);
    // mosquitto_publish(mosq, NULL, "/ynov/bordeaux/ProjetDroneCCPPemb", 3, "aaa", 2, false);

    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);




}
