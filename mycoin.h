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

	//�ı��־��ִ�з�תЧ��
	void ChangeFlag();

	void mousePressEvent(QMouseEvent *e);
signals:

public slots:

public:
    int m_posX;
    int m_posY;
    bool m_bFlag;//1�����ɫ��0������ɫ
	bool m_bWin;

private:
	QTimer* m_pTimerTop;//���淭ת��ʱ��
	QTimer* m_pTimerBottom;//���淭ת��ʱ��
	int m_iMin;
	int m_iMax;
	bool m_bIsAnimation;  //���ڷ�ת��־
	
};

#endif // MYCOIN_H
