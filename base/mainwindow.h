#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include "base.h"

class MainWindow : public QMainWindow 
{
    Q_OBJECT

public:
    MainWindow();

private:
    QLabel* imageLabel;
    QLabel* coordinatesLabel;
    MQTTImageReceiver* mqttImageReceiver;
};

#endif // MAINWINDOW_H
