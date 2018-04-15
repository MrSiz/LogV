#ifndef LOGPROCESSOR_H
#define LOGPROCESSOR_H
#include <QFile>
#include <QList>

class LogConfig;
class LogDataTable;

class LogProcessor
{
public:
    ~LogProcessor() = default;
    LogProcessor(const LogProcessor &) = delete;
    LogProcessor& operator =(const LogProcessor &) = delete;

private:
    LogProcessor();

    QList<QString> spliteByteArray(const QByteArray &arr, const char &a);

public:
    static LogProcessor *getLogProcessor();
    void start(const QString &path, LogConfig *logConfig = nullptr, LogDataTable *logDataTable = nullptr);
};

#endif // LOGPROCESSOR_H
