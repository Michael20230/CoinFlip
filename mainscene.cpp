#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"
#include "chooselevelscene.h"


#include<QDir>
#include <QDebug>
#include <QPainter>
#include <QFileInfo>
#include <QTimer>


MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //设置固定大小
    this->setFixedSize(320,588);
    //设置应用图片
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置窗口标题
    this->setWindowTitle(QString("翻金币"));
    //点击推出，推出程序
    connect(ui->actionQuit,&QAction::triggered,[=](){this->close();});
    //创建开始按钮MenuSceneStartButton
    MyPushButton* pStartBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    pStartBtn->setParent(this);
    qDebug()<<"this->width = "<<this->width()<<"  this->Height() = "<<this->height();
    pStartBtn->move(this->width()*0.5 - pStartBtn->width()*0.5,this->height()*0.7);
    //监听点击事件，执行特效
    connect(pStartBtn,&MyPushButton::clicked,[=](){
        pStartBtn->ZoomUp();
        pStartBtn->ZoomDown();
    });

    //选择关卡场景
//    ChooseLevelScene* pChooseScene =new  ChooseLevelScene();
//    QTimer::singleShot(500,this,[=](){
//        this->hide();
//        pChooseScene->show();
//    });
}


MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    //创建画家，指定绘图设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/res/PlayLevelSceneBg.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
