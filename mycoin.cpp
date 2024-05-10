#include "mycoin.h"


#include <QDebug>

#include <QPixmap>
#include <QTimer>


//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}

MyCoin::MyCoin(QString butImg) :
	m_iMax(8),
	m_iMin(1),
	m_bFlag(false),
	m_bIsAnimation(false),
	m_bWin(false)
{
    QPixmap pixmap;
    bool ret  = pixmap.load(butImg);
    if(!ret){
        qDebug()<<butImg<<"加载图片失败";
    }
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));

	m_pTimerTop = new QTimer(this);
	m_pTimerBottom= new QTimer(this);
	//监听正面翻转的信号槽
	connect(m_pTimerTop, &QTimer::timeout, [=]() {
		QPixmap pixmap;
		QString str = QString(":/res/Coin000%1.png").arg(m_iMin++);
		pixmap.load(str);
		this->setFixedSize(pixmap.width(), pixmap.height());
		this->setStyleSheet("QPushButton{border:0px;}");
		this->setIcon(pixmap);
		this->setIconSize(QSize(pixmap.width(), pixmap.height()));
		if (m_iMin > m_iMax) {
			m_iMin = 1;
			m_pTimerTop->stop();
			m_bIsAnimation = false;
		}
	});
	//监听反面翻转信号
	connect(m_pTimerBottom, &QTimer::timeout, [=]() {
		QPixmap pixmap;
		QString str = QString(":/res/Coin000%1.png").arg(m_iMax--);
		pixmap.load(str);
		this->setFixedSize(pixmap.width(), pixmap.height());
		this->setStyleSheet("QPushButton{QPushButton{border:0px;}");
		this->setIcon(pixmap);
		this->setIconSize(QSize(pixmap.width(), pixmap.height()));
		if (m_iMax < m_iMin) {
			m_iMax = 8;
			m_pTimerBottom->stop();
			m_bIsAnimation = false;
		}
	});
}

void MyCoin::ChangeFlag()
{
	m_bIsAnimation = true;
	if (m_bFlag) {
		m_pTimerTop->start(30);
		m_bFlag = false;
	}
	else {
		m_pTimerBottom->start(20);
		m_bFlag = true;
	}

}

void MyCoin::mousePressEvent(QMouseEvent * e)
{
	if (m_bIsAnimation || (m_bWin == true)) {
		return;
	}
	else {
		return QPushButton::mousePressEvent(e);
	}
}
