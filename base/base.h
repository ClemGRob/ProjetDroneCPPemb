#ifndef BASE_H
#define BASE_H

#include <QObject>
#include <QPixmap>
#include <QDebug>
#include "opencv2/opencv.hpp"
#include <mosquitto.h>

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

signals:
    void imageReceived(const QPixmap& image, float64_t lat, float64_t lon);

private:
    std::string topic_;
    struct mosquitto* mosq_;

    static void on_connect(struct mosquitto* mosq, void* obj, int rc);
    static void on_message(struct mosquitto* mosq, void* obj, const struct mosquitto_message* msg);
    void findHiddenCoordinates(const QByteArray& imageData, float64_t& lat, float64_t& lon);
    std::string extractLSBData(const cv::Mat& img);
};


#endif // BASE_H
