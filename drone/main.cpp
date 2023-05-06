#include <QImage>
#include <QColor>
#include <QFile>
#include <QString>
#include "pictureencoder.h"
#include <iostream>

int main()
{

    PictureEncoder pict("../../DroneIMG37337.png", "bb");
    cout<<pict.b_data_tab.toStdString();
    pict.encode_picture();
    cout<<pict.decode_picture().toStdString();


          return 0;

}
