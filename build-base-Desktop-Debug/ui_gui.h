/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_drone
{
public:
    QWidget *widget;
    QLineEdit *hidden_text;
    QPushButton *pb_connect;
    QPushButton *pb_picture;
    QPushButton *pb_hidden_text;
    QLineEdit *image;
    QLineEdit *broker_address;
    QLineEdit *picture_project;
    QMenuBar *menubar;
    QMenu *menu_PAQL;
    QMenu *menu_Images;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *drone)
    {
        if (drone->objectName().isEmpty())
            drone->setObjectName(QString::fromUtf8("drone"));
        drone->resize(800, 600);
        widget = new QWidget(drone);
        widget->setObjectName(QString::fromUtf8("widget"));
        hidden_text = new QLineEdit(widget);
        hidden_text->setObjectName(QString::fromUtf8("hidden_text"));
        hidden_text->setGeometry(QRect(20, 400, 511, 81));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        hidden_text->setFont(font);
        hidden_text->setReadOnly(true);
        pb_connect = new QPushButton(widget);
        pb_connect->setObjectName(QString::fromUtf8("pb_connect"));
        pb_connect->setGeometry(QRect(560, 90, 231, 28));
        pb_connect->setFont(font);
        pb_picture = new QPushButton(widget);
        pb_picture->setObjectName(QString::fromUtf8("pb_picture"));
        pb_picture->setGeometry(QRect(560, 130, 231, 28));
        pb_picture->setFont(font);
        pb_hidden_text = new QPushButton(widget);
        pb_hidden_text->setObjectName(QString::fromUtf8("pb_hidden_text"));
        pb_hidden_text->setGeometry(QRect(560, 170, 231, 28));
        pb_hidden_text->setFont(font);
        image = new QLineEdit(widget);
        image->setObjectName(QString::fromUtf8("image"));
        image->setEnabled(true);
        image->setGeometry(QRect(20, 20, 511, 361));
        image->setAlignment(Qt::AlignCenter);
        image->setReadOnly(true);
        broker_address = new QLineEdit(widget);
        broker_address->setObjectName(QString::fromUtf8("broker_address"));
        broker_address->setGeometry(QRect(560, 20, 231, 51));
        broker_address->setFont(font);
        broker_address->setAlignment(Qt::AlignCenter);
        broker_address->setReadOnly(true);
        broker_address->setClearButtonEnabled(false);
        picture_project = new QLineEdit(widget);
        picture_project->setObjectName(QString::fromUtf8("picture_project"));
        picture_project->setGeometry(QRect(560, 300, 231, 181));
        picture_project->setFont(font);
        picture_project->setAlignment(Qt::AlignBottom|Qt::AlignJustify);
        drone->setCentralWidget(widget);
        menubar = new QMenuBar(drone);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menu_PAQL = new QMenu(menubar);
        menu_PAQL->setObjectName(QString::fromUtf8("menu_PAQL"));
        menu_Images = new QMenu(menubar);
        menu_Images->setObjectName(QString::fromUtf8("menu_Images"));
        drone->setMenuBar(menubar);
        statusbar = new QStatusBar(drone);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        drone->setStatusBar(statusbar);

        menubar->addAction(menu_PAQL->menuAction());
        menubar->addAction(menu_Images->menuAction());

        retranslateUi(drone);

        QMetaObject::connectSlotsByName(drone);
    } // setupUi

    void retranslateUi(QMainWindow *drone)
    {
        drone->setWindowTitle(QApplication::translate("drone", "drone", nullptr));
        hidden_text->setText(QApplication::translate("drone", "Texte cach\303\251", nullptr));
        pb_connect->setText(QApplication::translate("drone", "Se connecter", nullptr));
        pb_picture->setText(QApplication::translate("drone", "Afficher l'image", nullptr));
        pb_hidden_text->setText(QApplication::translate("drone", "Afficher le texte cach\303\251", nullptr));
        image->setText(QString());
        broker_address->setText(QApplication::translate("drone", "Adresse du broker", nullptr));
        picture_project->setText(QApplication::translate("drone", "I3C", nullptr));
        menu_PAQL->setTitle(QApplication::translate("drone", "PAQL", nullptr));
        menu_Images->setTitle(QApplication::translate("drone", "Images", nullptr));
    } // retranslateUi

};

namespace Ui {
    class drone: public Ui_drone {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
