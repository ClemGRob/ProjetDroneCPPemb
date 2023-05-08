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
    void make_sendable();
    void encode_data();
    QString decode_picture();
    QString s_data;
    QByteArray b_data_tab;
    void make_sendableaa();
private:
    QString s_image_name;
    //QString s_data;

    QImage i_image;
};

#endif // PICTUREENCODER_H
