#include "mypushbutton.h"
#include <QDebug>
#include <QPixmap>
#include <QPropertyAnimation>


//MyPushButton::MyPushButton(QPushButton *parent) : QPushButton(parent)
//{
//    qDebug()<<"enter ,,";
//}

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    qDebug()<<"enter MyPushButton(QString normalImg, QString pressImg)";
    //成员变量normalImgPath保存正常显示图片路径
    m_normalImgPath = normalImg;
    //成员变量pressImgPath保存按下后显示的图片
    m_pressImgPath = pressImg;
    //创建QPixmap对象
    QPixmap pixmap;
    //判断是否能够加载正常显示的图片，若不能提示加载失败
    bool ret = pixmap.load(normalImg);
    if(!ret){
        qDebug()<<normalImg<<" 加载图片失败";
    }
    //设置图片的固定尺寸
    this->setFixedSize(pixmap.width(),pixmap.height());
    //设置不规则图片的样式表
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pixmap);
    //设置图标大小
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}

void MyPushButton::ZoomUp()
{
    qDebug()<<"enter zoom Up";
    //创建动画对象
    QPropertyAnimation* animation1 = new QPropertyAnimation(this,"geometry");
    //设置时间间隔，单位毫秒
    animation1->setDuration(200);
    //创建起始位置
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //创建结束位置
    animation1->setEndValue(QRect(this->x(),this->y()+20,this->width(),this->height()));
    //设置缓和曲线， QEasingCurve::OutBounce为弹跳效果
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation1->start();
}

void MyPushButton::ZoomDown()
{
    qDebug()<<"zoom Down";
    QPropertyAnimation* animation2 = new QPropertyAnimation(this,"geometry");
    animation2->setDuration(200);
    animation2->setStartValue(QRect(this->x(),this->y()+20,this->width(),this->height()));
    animation2->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation2->setEasingCurve(QEasingCurve::OutBounce);
    animation2->start();
}
