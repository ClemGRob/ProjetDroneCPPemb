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

void PictureEncoder::send_data()
{
    // QImage image("mon_image.png");

    mosquitto_lib_init();
    // Convertir l'image en base64
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    this->i_image.save(&buffer, "PNG");
    QString base64 = byteArray.toBase64();
    //char* ttt= base64.toStdString().c_str();
    printf("Contenu base64 : %s", base64.toStdString().c_str());

    // QImage image = QImage::fromData(base64.toStdString().c_str());
    // QImage image = QImage::fromData(byteArray, "PNG");
    
    struct mosquitto *mosq = mosquitto_new(NULL, true, NULL);
    mosquitto_connect(mosq, "broker.emqx.io", 1883, 60);
    mosquitto_loop_start(mosq);

    int decoupe = 1000;

    int num_chunks = base64.length() / decoupe;
    if (base64.length() % decoupe != 0)
    {
        num_chunks++;
    }
    for (int i = 0; i < num_chunks; i++)
    {
        int chunk_start = i * decoupe;
        int chunk_length = min((int)base64.length() - chunk_start, decoupe);
        string chunk = base64.mid(chunk_start, chunk_length).toStdString();
        printf("%s\n",chunk.c_str());
        printf("%d\n",i);
        mosquitto_publish(mosq, NULL, "/ynov/bordeaux/ProjetDroneCCPPemb", chunk_length, chunk.c_str(), 2, false);
        QTime dieTime= QTime::currentTime().addMSecs(100);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 10);

    }
    // mosquitto_publish(mosq, NULL, "/ynov/bordeaux/ProjetDroneCCPPemb", strlen(base64.toStdString().c_str()), base64.toStdString().c_str(), 2, false);

    mosquitto_publish(mosq, NULL, "/ynov/bordeaux/ProjetDroneCCPPemb", 3, "FIN", 2, false);
    mosquitto_loop_stop(mosq, true);
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);

    // QTime dieTime= QTime::currentTime().addMSecs(1000);
    //     while (QTime::currentTime() < dieTime)
    //         QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
    // mosquitto_lib_init();

    // struct mosquitto *mosq2 = mosquitto_new(NULL, true, NULL);
    // mosquitto_connect(mosq2, "broker.emqx.io", 1883, 60);


    // for (int i = num_chunks/2; i < num_chunks; i++)
    // {
    //     int chunk_start = i * decoupe;
    //     int chunk_length = min((int)base64.length() - chunk_start, decoupe);
    //     string chunk = base64.mid(chunk_start, chunk_length).toStdString();
    //     printf("%s\n",chunk.c_str());
    //     mosquitto_publish(mosq2, NULL, "/ynov/bordeaux/ProjetDroneCCPPemb", chunk_length, chunk.c_str(), 2, false);
    //     if(i == num_chunks/2)
    //     {QTime dieTime= QTime::currentTime().addMSecs(1000);
    //     while (QTime::currentTime() < dieTime)
    //         QCoreApplication::processEvents(QEventLoop::AllEvents, 10);}

    // }

    // mosquitto_publish(mosq2, NULL, "/ynov/bordeaux/ProjetDroneCCPPemb", 3, "FIN", 2, false);

    // mosquitto_disconnect(mosq2);
    // mosquitto_destroy(mosq2);
    




}
