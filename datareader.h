#ifndef DATAREADER_H
#define DATAREADER_H

#include "own.h"

#include <QObject>

class DataReader : public QObject
{
    Q_OBJECT
public:
    explicit DataReader(QObject *parent = nullptr);


    void initData();
signals:
    void send(int row, int col, const LogHeaders &header, const DataTable& data);

public slots:
    void getData();

private:
    QList<QString> spliteByteArray(const QByteArray &arr, const char &a);
    static LogHeaders getHeadFromConfig();
    static LogValidPos getPosFromConfig();
    static AnalysisItem getAnaItemFromConfig();
    static QString getDataPath();
    static char getDelimiter();
private:
    DataTable data;
    LogHeaders descriptions;
    LogValidPos validPos;
    AnalysisItem analysisItem;
    QString dataPath;
    char delimiter;
};

#endif // DATAREADER_H
