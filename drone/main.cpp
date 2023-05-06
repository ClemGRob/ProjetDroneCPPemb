#include <QImage>
#include <QColor>
#include <QFile>
#include <QString>
#include "pictureencoder.h"
#include <iostream>

int main()
{

    PictureEncoder pict("../../DroneIMG37337.png", "salut beaugosse");
    cout<<pict.b_data_tab.toStdString();
    pict.encode_picture();
    QString a(pict.decode_picture());
    cout<<"\nle résultat c'est : "<<a.toStdString();
    return 0;

}
