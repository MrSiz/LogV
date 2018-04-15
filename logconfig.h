#ifndef LOGCONFIG_H
#define LOGCONFIG_H
#include <QString>
#include <QVector>
#include <QFile>

class LogConfig
{
public:
    ~LogConfig();
    LogConfig(const LogConfig &) = delete;
    LogConfig& operator=(const LogConfig &) = delete;
private:
    LogConfig();

public:
    QString getDelimiter() const;
    QVector<QString> getDetail() const;
    static LogConfig *getLogConfig();
    void readConfig();

private:


private:
    QString delimiter;
    QVector<QString> vec;
};

#endif // LOGCONFIG_H
