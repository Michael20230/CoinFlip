#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QPaintEvent>

#include "chooselevel.h"

namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = 0);
    ~MainScene();
    void paintEvent(QPaintEvent *);

private:
    Ui::MainScene *ui;

    ChooseLevel* m_pChooseScene;
};

#endif // MAINSCENE_H
