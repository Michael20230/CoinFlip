#ifndef PLAYSCENE_H
#define PLAYSCENE_H

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
};

#endif // PLAYSCENE_H
