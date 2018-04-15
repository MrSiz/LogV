#ifndef LOGCOLLECTOR_H
#define LOGCOLLECTOR_H

#include <QObject>

class QTimer;

class LogCollector : public QObject
{
    Q_OBJECT
public:
    ~LogCollector();
    LogCollector(const LogCollector &) = delete;
    LogCollector& operator =(const LogCollector &) = delete;

private:
       explicit LogCollector(QObject *parent = nullptr);

public:
//start collecting the logs
    void start(int mis);
    static LogCollector* getLogCollector();

private:
    void stop();

signals:

public slots:
    void downloadLog();

private:
    QTimer *timer;
};

#endif // LOGCOLLECTOR_H
