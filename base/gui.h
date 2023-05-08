#ifndef DRONE_H
#define DRONE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    virtual ~GUI();


private:
    Ui::GUI *ui;
    void on_showTextButton_clicked();
    void on_getBrokerAddressButton_clicked();
    void on_getImageButton_clicked();
};
#endif // DRONE_H
