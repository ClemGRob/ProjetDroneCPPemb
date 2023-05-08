#ifndef PICTUREENCODER_H
#define PICTUREENCODER_H
#include <QString>
#include "../includes/PAQL.h"
#include <QImage>
class PictureEncoder
{
public:
    PictureEncoder(QString s_image_name,QString s_data);
    void encode_picture();
    void send_data();
    QString s_decode_picture();
    QString s_data;
private:
    QString s_image_name;
    QImage i_image;
};

#endif // PICTUREENCODER_H
