#include <QImage>
#include <QColor>
#include <QFile>
#include <QString>
#include "pictureencoder.h"
#include <iostream>

int main()
{
    PictureEncoder pict("../DroneIMG37337.png", "37°42'41.9\"S 144°59'33.0\"E");
    pict.b_data_tab.toStdString();
    pict.encode_picture();
    pict.send_data();
    return 0;

}
