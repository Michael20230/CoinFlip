#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QObject>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QPushButton *parent = nullptr);//QWidget *parent = nullptr
    MyPushButton(QString normalImg,QString pressImg="");


public slots:
    void ZoomUp();
    void ZoomDown();

private:
    QString m_normalImgPath;
    QString m_pressImgPath;
};

#endif // MYPUSHBUTTON_H
