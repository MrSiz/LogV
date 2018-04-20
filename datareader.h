#ifndef DATAREADER_H
#define DATAREADER_H

#include "own.h"

#include <QObject>

class DataReader : public QObject
{
    Q_OBJECT
public:
    explicit DataReader(QObject *parent = nullptr);
    LogHeaders getFromConfig();

signals:
    void send(int row, int col, const LogHeaders &header, const DataTable& data);

public slots:
    void getData();



private:
    DataTable data;
    LogHeaders descriptions;
};

#endif // DATAREADER_H
