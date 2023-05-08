#ifndef BASE_H
#define BASE_H

#include <QObject>
#include <QPixmap>
#include <QDebug>
#include <mosquitto.h>
#include <QImage>

typedef char char_t;
typedef float float32_t;
typedef double float64_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long int64_t;

class MQTTImageReceiver : public QObject {
    Q_OBJECT

public:
    MQTTImageReceiver(const std::string& topic);
    ~MQTTImageReceiver();
    static void base64ToImage();
    static QString decode_picture();

signals:
    void imageReceived(const QPixmap& image, float64_t lat, float64_t lon);

private:
    std::string topic_;
    struct mosquitto* mosq_;
    static std::vector<unsigned char> m_imageData;

    static void on_connect(struct mosquitto* mosq, void* obj, int rc);
    static void on_message(struct mosquitto* mosq, void* obj, const struct mosquitto_message* msg);

};


#endif // BASE_H
