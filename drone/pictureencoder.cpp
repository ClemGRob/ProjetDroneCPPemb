#include "pictureencoder.h"
#include <QString>
#include <bitset>
#include <iostream>
#include <QByteArray>
PictureEncoder::PictureEncoder(QString s_image_name,QString s_data)
{
    this->s_image_name = s_image_name;
    this->s_data = s_data;//QString::number(s_data.length()) + QString("S")+ s_data;
    this->b_data_tab = this->s_data.toStdString().c_str();//.toUtf8();


}


void PictureEncoder::encode_data()
{

}

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
                printf("pixel : %d  ",pixels[pixel_cmp]);
                if(((byte >> k) & 1)==1)
                    {pixels[pixel_cmp]|= 0x01;
                    printf("to 1 ");}
                else
                    {pixels[pixel_cmp]&= 0xFE;
                    printf("to 0 ");}
                printf("%d\n",pixels[pixel_cmp]);
                pixel_cmp+=1;
                
            }
        }
    }


}

QString PictureEncoder::decode_picture()
{

    QByteArray messageData;
    const unsigned char *pixels = this->i_image.bits();
    int imageSize = this->i_image.width() * this->i_image.height();

    for (int i = 0; i < 7*8; i++) {
        unsigned char lastBit = pixels[i] & 0x01;
        messageData.append(lastBit);
    }

    QString message = QString::fromUtf8(messageData);
    printf("aa\n%s\n",message.toStdString());
    return message;

    
    // const unsigned char *pixels = this->i_image.bits();
    // int imageSize = this->i_image.width() * this->i_image.height();

    // // Récupérer la taille du message caché
    // int messageSize = 0;
    // for (int i = 0; i < 8; i++) {
    //     int bit = pixels[i] & 1;
    //     messageSize |= (bit << i);
    // }

    // // Vérifier que la taille du message est cohérente avec l'image
    // if (messageSize + 8 > imageSize) {
    //     printf("erorsize");
    //     //qDebug() << "Le message n'a pas été trouvé dans l'image.";
    //     return "";
    // }

    // // Récupérer le message caché
    // QByteArray messageData;
    // for (int i = 0; i < messageSize; i++) {
    //     unsigned char byte = 0;
    //     for (int j = 0; j < 8; j++) {
    //         int bit = pixels[(i+1)*8+j] & 1;
    //         byte |= (bit << j);
    //     }
    //     messageData.append(byte);
    // }

    // // Vérifier le préfixe du message
    // QString message = QString::fromUtf8(messageData);
    // if (!message.startsWith("S")) {
    //     printf("eroS");
    //     //qDebug() << "Le message n'a pas été trouvé dans l'image.";
    //     return message;
    // }

    // // Extraire le message de la chaîne
    // int messageLength = message.mid(1, 8).toInt();
    // message = message.mid(9, messageLength);

    // return message;
}
    // int imageSize = this->i_image.width() * this->i_image.height();
    // QString message = this->s_data;

    // int messageSize = this->b_data_tab.size();
    // unsigned char *messageBytes = (unsigned char *)this->b_data_tab.constData();

    // if (messageSize > imageSize) {
    //     printf("Le message est trop grand pour être caché dans l'image.");
    //     return;
    // }


//     int i = 0;

    // for (int y = 0; y < this->i_image.height(); y++) {
    //    for (int x = 0; x < this->i_image.width(); x++) {
    //        QRgb pixel = this->i_image.pixel(x, y);
    //        int gray = qGray(pixel);

    //        this->i_image.setPixel(x, y, gray);
    //    }
    //    }
           
//         //    if (this->b_data_tab.length() > 0) {
//         //         i++;
//         //        gray = (gray & ~1) | (this->b_data_tab.at(0));
//         //        //if(gray%2 == 0 and )
               
//         //        this->b_data_tab.remove(0, 1);
//         //        printf("\ndata restance : %d",this->b_data_tab.length());
//         //    }
//         //    
//        }
//    }
//     this->i_image.save("../../test2_DroneIMG37337.png");
//     printf("\n nb rep : %d",i);

    // // encode number
    // for(int i = 0; i < this->b_data_tab.length(); i++)
    // {
    //     pixels[(i-1)*8+k]
    // }
    // if()
    // int i = 0;


    // while (i < messageSize) {
    //     if (messageBytes[i] >= '0' && messageBytes[i] <= '9') {
    //         // Cacher le nombre de caractères du message
    //         int length = messageBytes[i] - '0';
    //         i++;
    //         for (int j = 0; j < length && i < messageSize; j++) {
    //             // Cacher chaque caractère du message
    //             for (int k = 0; k < 8 && i < messageSize; k++) {
    //                 int bit = (messageBytes[i] >> k) & 1;
    //                 pixels[(i-1)*8+k] = (pixels[(i-1)*8+k] & 0xFE) | bit;
    //             }
    //             i++;
    //         }
    //     } else {
    //         i++;
    //     }
    // }

void PictureEncoder::make_sendable()
{

}
