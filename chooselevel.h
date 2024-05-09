#ifndef CHOOSELEVEL_H
#define CHOOSELEVEL_H

#include <QMainWindow>
#include <QPaintEvent>


class ChooseLevel : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevel(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);
signals:
    void chooseSceneBack();
public slots:
};

#endif // CHOOSELEVEL_H
