#include "playscene.h"
#include "mypushbutton.h"
#include "mycoin.h"
#include "dataconfig.h"


#include <QMenuBar>
#include <QMenu>
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>
#include <QSound>


//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int iIndex):
	m_bIsWin(false)
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

	//音效
	QSound* pBackSound = new QSound(":/res/BackButtonSound.wav", this);
	QSound* pFlipSound = new QSound(":/res/ConFlipSound.wav", this);
	QSound* pWinSound = new QSound(":/res/LevelWinSound.wav", this);

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

    //初始化二维数组(关卡数据)
    DataConfig config;
    for(int i=0; i<4; i++){
        for(int j =0; j<4; j++){
            m_arrayGame[i][j] = config.m_mapData[m_iLevelIndex][i][j];
        }
    }

	
	//胜利图片
	QLabel* winLabel = new QLabel;
	QPixmap tmpPix;
	tmpPix.load(":/res/LevelCompletedDialogBg.png");
	winLabel->setGeometry(0, 0, tmpPix.width(), tmpPix.height());
	winLabel->setPixmap(tmpPix);
	winLabel->setParent(this);
	winLabel->move((this->width() - tmpPix.width())*0.5, tmpPix.height());
	winLabel->setWindowFlags(Qt::WindowStaysOnTopHint);
	winLabel->hide();


    //创建金币背景图片
    for(int i=0 ; i<4; i++){
        for(int j=0; j<4; j++){
            //绘制背景图片
            QLabel* label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->setParent(this);
            label->move(57+i*50,200+j*50);

            //金币对象
            QString strImgPath;
            if(m_arrayGame[i][j] == 1){
                strImgPath = ":/res/Coin0001.png";
            }
            else{
                strImgPath = ":/res/Coin0008.png";
            }
            MyCoin* coin = new MyCoin(strImgPath);
			m_coinBtn[i][j] = coin;
            coin->setParent(this);
            coin->move(59+i*50, 204+j*50);
            coin->m_posX = i;
            coin->m_posY = j;
			coin->m_bFlag = m_arrayGame[i][j] == 0 ? false:true;
			connect(coin, &MyCoin::clicked, [=]() {
				//翻转被点击的金币
				coin->ChangeFlag();
				m_arrayGame[i][j] = m_arrayGame[i][j] == 0 ? 1 : 0;
				//翻转音效
				pFlipSound->play();
				//翻转其他金币
				QTimer::singleShot(300, this, [=]() {
					if (coin->m_posX  < 3) {
						m_arrayGame[i + 1][j] = m_arrayGame[i+1][j] == 0 ? 1 : 0;
						m_coinBtn[i + 1][j]->ChangeFlag();
					}
					if (coin->m_posX > 0) {
						m_arrayGame[i-1][j] = m_arrayGame[i-1][j] == 0 ? 1 : 0;
						m_coinBtn[i-1][j]->ChangeFlag();
					}
					if (coin->m_posY < 3) {
						m_arrayGame[i][j + 1] = m_arrayGame[i][j+1] == 0 ? 1 : 0;
						m_coinBtn[i][j + 1]->ChangeFlag();
					}
					if (coin->m_posY > 0) {
						m_arrayGame[i][j - 1] = m_arrayGame[i][j-1] == 0 ? 1 : 0;
						m_coinBtn[i][j - 1]->ChangeFlag();
					}

					//判断是否胜利
					m_bIsWin = true;
					for (int k = 0; k < 4; k++) {
						for (int m = 0; m < 4; m++) {
							bool ret = m_coinBtn[k][m]->m_bFlag;
							if (m_coinBtn[k][m]->m_bFlag == false) {
								m_bIsWin = false;
								break;
							}
						}
					}
					if (m_bIsWin) {
						pWinSound->play();
						winLabel->show();

						//成功界面动画
						QPropertyAnimation* animation1 = new QPropertyAnimation(winLabel, "geometry");
						animation1->setDuration(1000);
						animation1->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
						animation1->setEndValue(QRect(winLabel->x(), winLabel->y() + 30, winLabel->width(), winLabel->height()));
						animation1->setEasingCurve(QEasingCurve::OutBounce);
						animation1->start();
						//禁用所有按钮点击事件
						for (int k = 0; k < 4; k++) {
							for (int m = 0; m < 4; m++) {
								m_coinBtn[k][m]->m_bWin = true;
							}
						}
					}
				});

				
				
			});
        }
    }

	


}

void PlayScene::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
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






