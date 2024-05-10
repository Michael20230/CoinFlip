#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QObject>
#include <QPushButton>
#include <QMouseEvent>


class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString butImg);

	//改变标志，执行翻转效果
	void ChangeFlag();

	void mousePressEvent(QMouseEvent *e);
signals:

public slots:

public:
    int m_posX;
    int m_posY;
    bool m_bFlag;//1代表金色，0代表银色
	bool m_bWin;

private:
	QTimer* m_pTimerTop;//正面翻转定时器
	QTimer* m_pTimerBottom;//反面翻转定时器
	int m_iMin;
	int m_iMax;
	bool m_bIsAnimation;  //正在翻转标志
	
};

#endif // MYCOIN_H
