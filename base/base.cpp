#include "base.h"
#include "mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QFile>
#include <QPixmap>
#include <QWidget>

MQTTImageReceiver::MQTTImageReceiver(const std::string& topic) : topic_(topic) {
    const char* ADDRESS = "broker.emqx.io";
    const int PORT = 1883;
    const int KEEP_ALIVE = 60;

    mosquitto_lib_init();
    mosq_ = mosquitto_new(NULL, true, this);

    if (!mosq_) {
        qDebug() << "Error initializing Mosquitto";
        return;
    }

    mosquitto_connect_callback_set(mosq_, on_connect);
    mosquitto_message_callback_set(mosq_, on_message);

    int ret = mosquitto_connect(mosq_, ADDRESS, PORT, KEEP_ALIVE);
    if (ret != MOSQ_ERR_SUCCESS) {
        qDebug() << "Error connecting to Mosquitto";
        return;
    }

    ret = mosquitto_subscribe(mosq_, NULL, topic.c_str(), 2);
    if (ret != MOSQ_ERR_SUCCESS) {
        qDebug() << "Error subscribing to Mosquitto topic";
        return;
    }

    ret = mosquitto_loop_start(mosq_);
    if (ret != MOSQ_ERR_SUCCESS) {
        qDebug() << "Error starting Mosquitto loop";
        return;
    }
}

MQTTImageReceiver::~MQTTImageReceiver() {
    if (mosq_) {
        mosquitto_loop_stop(mosq_, true);
        mosquitto_disconnect(mosq_);
        mosquitto_destroy(mosq_);
    }
    mosquitto_lib_cleanup();
}

void MQTTImageReceiver::on_connect(struct mosquitto* mosq, void* obj, int rc) {
    if (rc != 0) {
        qDebug() << "Error connecting to Mosquitto: " << rc;
    }
}

void MQTTImageReceiver::on_message(struct mosquitto* mosq, void* obj, const struct mosquitto_message* msg) {
    MQTTImageReceiver* receiver = static_cast<MQTTImageReceiver*>(obj);
    QByteArray imageData(static_cast<char*>(msg->payload), msg->payloadlen);
    QPixmap pixmap;
    pixmap.loadFromData(imageData);

     // Découvrir les coordonnées GPS cachées dans l'image
    float64_t lat, lon;
    receiver->findHiddenCoordinates(imageData, lat, lon);

    emit receiver->imageReceived(pixmap, lat, lon);
}

void MQTTImageReceiver::findHiddenCoordinates(const QByteArray& imageData, float64_t& lat, float64_t& lon) {
    cv::Mat rawData(1, imageData.size(), CV_8UC1, const_cast<uchar*>(reinterpret_cast<const uchar*>(imageData.data())));
    cv::Mat img = imdecode(rawData, cv::IMREAD_COLOR);

    if (img.empty()) {
        qDebug() << "Failed to decode image";
        return;
    }

    std::string hiddenData = extractLSBData(img);
    size_t delimiterPos = hiddenData.find(',');

    if (delimiterPos != std::string::npos) {
        lat = std::stod(hiddenData.substr(0, delimiterPos));
        lon = std::stod(hiddenData.substr(delimiterPos + 1));
    } else {
        qDebug() << "Failed to extract hidden coordinates";
    }
}

std::string MQTTImageReceiver::extractLSBData(const cv::Mat& img) {
    std::string hiddenData;

    int dataBitIdx = 0;
    char currentChar = 0;

    for (int row = 0; row < img.rows; ++row) {
        for (int col = 0; col < img.cols; ++col) {
            for (int channel = 0; channel < 3; ++channel) {
                uchar pixel = img.at<cv::Vec3b>(row, col)[channel];
                currentChar |= (pixel & 1) << dataBitIdx;

                if (++dataBitIdx == 8) {
                    if (currentChar == '\0') {
                        return hiddenData;
                    }

                    hiddenData.push_back(currentChar);
                    dataBitIdx = 0;
                    currentChar = 0;
                }
            }
        }
    }

    return hiddenData;
}

