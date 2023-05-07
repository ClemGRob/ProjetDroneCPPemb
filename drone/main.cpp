#include <QImage>
#include <QColor>
#include <QFile>
#include <QString>
#include "pictureencoder.h"
#include "mqttpub.h"
#include <iostream>

int main()
{
    
    PictureEncoder pict("../DroneIMG37337.png", "salut beaugosse");
    printf("wtf?");
    cout<<pict.b_data_tab.toStdString();
    pict.encode_picture();
    pict.make_sendable();
    // QString a(pict.decode_picture());
    // MQTTImageReceiver b("/ynov/bordeaux/ProjetDroneCCPPemb");
    // b.pub("hello");
    // printf("toutbon");
    return 0;

}
