#include "mainwindow.h"

MainWindow::MainWindow() 
{

    imageLabel = new QLabel(this);
    coordinatesLabel = new QLabel(this);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(imageLabel);
    layout->addWidget(coordinatesLabel);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    mqttImageReceiver = new MQTTImageReceiver("/ynov/bordeaux/ProjetDroneCCPPemb");
}
