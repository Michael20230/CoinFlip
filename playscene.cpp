#include "playscene.h"
#include "mypushbutton.h"

#include <QMenuBar>
#include <QMenu>
#include <QPainter>
#include <QDebug>
#include <QLabel>


//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int iIndex)
{

    m_iLevelIndex = iIndex;
    qDebug()<<"enter PlayScene , "<<m_iLevelIndex;
    //设置窗口固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币");
    //创建菜单栏
    QMenuBar* bar = this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu* pStartMenu = bar->addMenu("开始");
    //创建按钮菜单项
    QAction* quitAction = pStartMenu->addAction("退出");
    //点击退出，退出游戏
    connect(quitAction,&QAction::triggered,[=](){this->close();});

    //返回按钮
    MyPushButton* pBackBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    pBackBtn->setParent(this);
    pBackBtn->move(this->width()-pBackBtn->width(),this->height()-pBackBtn->height());
    //返回按钮功能实现
    connect(pBackBtn,&MyPushButton::clicked,[=](){
        this->hide();
        //触发自定义信号，关闭自身
        emit chooseScene();
    });


    //显示当前关卡
    QLabel* label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString str = QString("Level:%1").arg(m_iLevelIndex);
    qDebug()<<"str = "<<str;
    label->setText(str);
    label->setGeometry(QRect(30,this->height()-50, 180, 50));

    //创建金币背景图片
    for(int i=0 ; i<4; i++){
        for(int j=0; j<4; j++){
            //绘制背景图片
            QLabel* label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->setParent(this);
            label->move(57+i*50,200+j*50);

        }
    }


}

void PlayScene::paintEvent(QPaintEvent *event)
{
    //加载背景
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
    //加载标题
    pixmap.load(":/res/Title.png");
    pixmap = pixmap.scaled(pixmap.width()*0.5, pixmap.height()*0.5);
    painter.drawPixmap(10,30,pixmap.width(),pixmap.height(),pixmap);


}






