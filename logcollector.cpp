#include "logcollector.h"
#include <QTimer>
#include <QProcess>
#include <QDebug>

LogCollector::LogCollector(QObject *parent) :
    QObject(parent),
    timer(new QTimer())
{
    connect(timer, SIGNAL(timeout()), this, SLOT(downloadLog()));
}

LogCollector::~LogCollector()
{
    qDebug() << "LogCollector destructor called";
    timer->stop();
    delete timer;
}

void LogCollector::start(int mis)
{
    timer->start(mis);
}

LogCollector *LogCollector::getLogCollector()
{
    static LogCollector collctor;
    return &collctor;
}

void LogCollector::stop()
{
    timer->stop();
}

void LogCollector::downloadLog()
{
    QProcess::execute("python /home/mrsiz/down.py");
}
