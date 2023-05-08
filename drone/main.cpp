#include <QImage>
#include <QColor>
#include <QFile>
#include <QString>
#include "pictureencoder.h"
#include <iostream>

int main()
{
    PictureEncoder pict("../DroneIMG37337.png", "aaa");
    cout<<pict.b_data_tab.toStdString();
    pict.encode_picture();
    pict.send_data();
    return 0;

}
