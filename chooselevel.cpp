#include "chooselevel.h"
#include "mypushbutton.h"


#include <QMenu>
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>



ChooseLevel::ChooseLevel(QWidget *parent) : QMainWindow(parent)
{
    //设置窗口固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡");
    //创建菜单栏
    QMenuBar* bar = this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu* pStartMenu = bar->addMenu("开始");
    //创建按钮菜单项
    QAction* quitAction = pStartMenu->addAction("退出");
    //点击退出，退出游戏
    connect(quitAction,&QAction::triggered,[=](){this->close();});
    //创建返回按钮
    MyPushButton* pCloseBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    pCloseBtn->setParent(this);
    pCloseBtn->move(this->width()-pCloseBtn->width(),this->height()-pCloseBtn->height());
    connect(pCloseBtn,&MyPushButton::clicked,[=](){
        QTimer::singleShot(500,this,[=](){
            this->hide();
            emit this->chooseSceneBack();
        });
    });
    //创建关卡按钮
    for(int i=0; i<20; i++){
        MyPushButton* menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+(i%4)*70,130+(i/4)*70);

        //按钮上显示的文字
        QLabel* label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        label->move(25+(i%4)*70,130+(i/4)*70);
        //鼠标穿透事件
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true);

    }
}

void ChooseLevel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);



}




