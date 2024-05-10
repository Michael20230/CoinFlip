#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "mycoin.h"

#include <QMainWindow>
#include <QPaintEvent>


class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
     PlayScene(int iIndex);

     void paintEvent(QPaintEvent *event);
signals:
     void chooseScene();

public slots:

private:
    int m_iLevelIndex;
    int m_arrayGame[4][4];//游戏关卡数据
	MyCoin* m_coinBtn[4][4];
	bool m_bIsWin;
};

#endif // PLAYSCENE_H
