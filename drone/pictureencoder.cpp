#include "pictureencoder.h"
#include <QString>
#include <bitset>
#include <iostream>
#include <QByteArray>
#include <QtCore/QBitArray>
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
    this->i_image = QImage("../../test_DroneIMG37337.png");
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

}
