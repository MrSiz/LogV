#include "logprocessor.h"
//#include <QTextStream>
#include <QDebug>

LogProcessor::LogProcessor()
{

}

LogProcessor *LogProcessor::getLogProcessor()
{
    static LogProcessor logProcessor;
    return &logProcessor;
}

void LogProcessor::start(const QString &path, LogConfig *logConfig, LogDataTable *logDataTable)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    auto cnt = 0;
    while (!file.atEnd()) {
        QByteArray byteArray = file.readLine();
        qDebug() << byteArray;
        ++cnt;
    }
    qDebug() << "total is " << cnt;
}

