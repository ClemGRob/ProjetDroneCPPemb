#include "pictureencoder.h"
#include <QString>
#include <QByteArray>
#include<mosquitto.h>
#include<QBuffer>
#include<QCoreApplication>
#include<QTime>

PictureEncoder::PictureEncoder(QString s_image_name,QString s_data)
{
    this->s_image_name = s_image_name;
    this->s_data = s_data + QString("\t");
}

void PictureEncoder::encode_picture()
{
    this->i_image = QImage(this->s_image_name);
    unsigned char *c_pixels_ptr = this->i_image.bits();
    int s32_pixel_cmp = 0;
    for (int s32_pixel_index = 0; s32_pixel_index < this->s_data.length(); s32_pixel_index++) {
        //chaque caractere
        QByteArray utf8 = this->s_data.mid(s32_pixel_index, 1).toUtf8();
        const char* c_data_ptx = utf8.data();
        for (int j = 0; j < utf8.length(); j++) {
            //chaque bit
            unsigned char c_byte = c_data_ptx[j];
            for (int k = 7; k >= 0; k--) {
                //chaque pixel
                if(((c_byte >> k) & 1)==1)
                    c_pixels_ptr[s32_pixel_cmp]|= 0x01;
                else
                    c_pixels_ptr[s32_pixel_cmp]&= 0xFE;
                s32_pixel_cmp+=1;
                
            }
        }
    }


}

void PictureEncoder::send_data()
{
    // save picture in buffer so we can send it later
    mosquitto_lib_init();
    QByteArray byteArray_tab;
    QBuffer buffer(&byteArray_tab);
    buffer.open(QIODevice::WriteOnly);
    this->i_image.save(&buffer, "PNG");
    QString s_base64 = byteArray_tab.toBase64();


    
    struct mosquitto *st_mosq_ptr = mosquitto_new(NULL, true, NULL);
    mosquitto_connect(st_mosq_ptr, "broker.emqx.io", 1883, 60);
    mosquitto_loop_start(st_mosq_ptr);

    const int s32_number_char_to_send = 1000;

    int s32_num_chunks = s_base64.length() / s32_number_char_to_send;
    if (s_base64.length() % s32_number_char_to_send != 0)
    {
        s32_num_chunks++;
    }
    for (int i = 0; i < s32_num_chunks; i++)
    {
        const int s32_chunk_start = i * s32_number_char_to_send;
        int chunk_length = min((int)s_base64.length() - s32_chunk_start, s32_number_char_to_send);
        string s_chunk = s_base64.mid(s32_chunk_start, chunk_length).toStdString();

        mosquitto_publish(st_mosq_ptr, NULL, "/ynov/bordeaux/ProjetDroneCCPPemb", chunk_length, s_chunk.c_str(), 2, false);

        //base can't reach all datas without a timer
        QTime dieTime= QTime::currentTime().addMSecs(100);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 10);

    }
    
    mosquitto_publish(st_mosq_ptr, NULL, "/ynov/bordeaux/ProjetDroneCCPPemb", 3, "FIN", 2, false);
    mosquitto_loop_stop(st_mosq_ptr, true);
    mosquitto_disconnect(st_mosq_ptr);
    mosquitto_destroy(st_mosq_ptr);
}
