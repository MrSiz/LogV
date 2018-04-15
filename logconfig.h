#ifndef LOGCONFIG_H
#define LOGCONFIG_H
#include <QString>
#include <QList>
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
    QList<QString> getDescriptionVec() const;
    QList<int> getPositionVec() const;
    static LogConfig *getLogConfig();
    void readConfig();

private:


private:
    QString delimiter;
//    description
    QList<QString> des;
//    position of des
    QList<int> pos;
};

#endif // LOGCONFIG_H
