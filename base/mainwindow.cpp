#include "mainwindow.h"

MainWindow::MainWindow() {
    imageLabel = new QLabel(this);
    coordinatesLabel = new QLabel(this);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(imageLabel);
    layout->addWidget(coordinatesLabel);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    mqttImageReceiver = new MQTTImageReceiver("/ynov/bordeaux/ProjetDroneCCPPemb");
    connect(mqttImageReceiver, &MQTTImageReceiver::imageReceived, this, [this](const QPixmap& image, float64_t lat, float64_t lon) {
        imageLabel->setPixmap(image);
        coordinatesLabel->setText(QString("Latitude: %1\nLongitude: %2").arg(lat).arg(lon));
    });
}
