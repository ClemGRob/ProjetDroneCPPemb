#include "gui.h"

#include <QFile>
#include <QImage>

#include "mosquitto.h"

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::drone)
{
    ui->setupUi(this);

    /*** Défini les paramètres de la fenêtre ***/

    setWindowTitle("I3C Projet C++"); // Titre
    setMinimumSize(400, 300); // Taille minimale
    setMaximumSize(800, 550); // Taille maximum
    setWindowIcon(QIcon("C:/Users/user/Documents/projet_drone_base/images/drone_fond.jpg")); // Icône de la fenêtre

    /*** Défini le style des widgets ***/

    /**Les widgets associés au texte caché**/
    ui->hidden_text->setStyleSheet("background-color: rgb(195, 176, 145); color: black;"); // couleur kaki : rgb(195, 176, 145)
    ui->pb_hidden_text->setStyleSheet("background-color: rgb(195, 176, 145); color: black; border: 2px solid white; border-radius: 20px");

    /**Les widgets associés à l'image drone**/
    ui->image->setStyleSheet("background-color: #F5F5DC; color: black;");
    ui->pb_picture->setStyleSheet("background-color: #F5F5DC; color: black; border: 2px solid white; border-radius: 20px");

    /**Les widgets associés au broker**/
    ui->broker_address->setStyleSheet("background-color: lightgreen; border: 2px solid white; border-radius: 20px"); // couleur beige : #F5F5DC
    ui->pb_connect->setStyleSheet("background-color: lightgreen; border: 2px solid white; border-radius: 20px");

    /**L'image donné pour le projet (design)**/
    ui->picture_project->setReadOnly(true);
    QString imagePath_project = "C:/Users/user/Documents/projet_drone_base/images/drone_fond.jpg";  // Chemin vers l'image
    QString style = QString("QLineEdit { background-image: url(%1); }").arg(imagePath_project);     // Affiche l'image dans le lineEdit
    ui->picture_project->setStyleSheet(style);

    /*** Défini les actions pour chaques boutons ***/

    /**Bouton pour afficher le texte caché**/
    connect(ui->pb_hidden_text, &QPushButton::clicked, this, [this]()
    {
        ui->hidden_text->setText("Les coordonnées du lieu : 37°42'41.9'S144°59'33.0'E");  // Affiche le texte caché
        ui->hidden_text->setReadOnly(true);
    });

    /**Bouton pour se connecter au Broker**/
    connect(ui->pb_connect, &QPushButton::clicked, this, [this]()
    {
        ui->broker_address->setReadOnly(true);
        QString brokerAddress = "broker.emqx.io";   // Récupère l'adresse du broker
        ui->broker_address->setText(brokerAddress); // Affiche l'adresse du broker dans le label
    });

    /**Bouton pour afficher l'image prise par le drone**/
    connect(ui->pb_picture, &QPushButton::clicked, this, [this]()
    {
        ui->image->setReadOnly(true);
        QString imagePath = "C:/Users/user/Documents/projet_drone_base/images/DroneIMG37337.png";  // Chemin vers l'image
        QString style = QString("QLineEdit { background-image: url(%1); }").arg(imagePath);        // Afficher l'image dans le lineEdit
        ui->image->setStyleSheet(style);
    });
}

GUI::~GUI()
{
    delete ui;
}
