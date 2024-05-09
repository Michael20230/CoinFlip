#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QObject>
#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString butImg);

signals:

public slots:
};

#endif // MYCOIN_H
