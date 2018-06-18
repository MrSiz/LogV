#ifndef DATAREADER_H
#define DATAREADER_H

#include "own.h"
#include "threadpool.h"

#include <QObject>

class DataReader : public QObject
{
    Q_OBJECT
public:
    explicit DataReader(int numThread = 10, QObject *parent = nullptr);


    void initData();
    int getAnalysisNum() const;
signals:
//    void numOfGraph(int n);
    void send(int row, int col, const LogHeaders &header, const DataTable& data);
    void pieChart(QList<int> data, QStringList xnames, QString title, int g_pos);
    void barChart(QList<int> data, QStringList xnames, QString title, int g_pos);
    void lineChart(QList<int> data, QStringList xnames, QString title, int g_pos);

    //get, head, post, put, del, trace
    void httpMethodAndTimeChart(QMap<int, int> get, QMap<int, int> head, QMap<int, int> post, QMap<int, int> put,
                           QMap<int, int> del, QMap<int, int> trace);
    void ipAndHttpReq(QMap<QString, QMap<QString, int>> store);

    void browserIpStatus(QHash<QString, int>, QHash<QString, QHash<QString, int>>,  QHash<QString, QHash<QString, QHash<QString, int>>>);

    void ipAndOs(QMap<QString, int> visitors, QMap<QString, int> hits, QStringList head);
public slots:
    void getData();

private:
    QList<QString> spliteByteArray(const QByteArray &arr, const char &a);
    static LogHeaders getHeadFromConfig();
    static LogValidPos getPosFromConfig();
    static AnalysisItem getAnaItemFromConfig();
    static QString getDataPath();
    static char getDelimiter();
    OneColLog getColLog(int index) const;
    void process(const OneColLog& colLog, int g_pos);

    void TwoDprocess(const OneColLog& log1, const OneColLog &log2, int g_pos);
    void processIpAndHttpRequest(const OneColLog &ip, const OneColLog &request);
    void processBrowserIpStatus(const OneColLog &browser, const OneColLog &ip, const OneColLog &status);
    void processIpAndOs(const OneColLog &ip, const OneColLog &userAgent);



private:
    DataTable data;
    LogHeaders descriptions;
    LogValidPos validPos;
    AnalysisItem analysisItem;
//    int graphNum;
    QString dataPath;
    char delimiter;
    ThreadPool pool;
};

#endif // DATAREADER_H
