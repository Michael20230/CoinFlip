#ifndef DATACONFIG_H
#define DATACONFIG_H
#include <QMap>
#include <QVector>



class DataConfig
{
public:
    DataConfig();
public:
    QMap<int,QVector<QVector<int>>> m_mapData;
};

#endif // DATACONFIG_H
