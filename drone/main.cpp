#include "pictureencoder.h"

int main()
{
    PictureEncoder pict("../DroneIMG37337.png", "37°42'41.9\"S 144°59'33.0\"E");
    pict.encode_picture();
    pict.send_data();
    return 0;

}
