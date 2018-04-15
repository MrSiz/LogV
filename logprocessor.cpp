#include "logprocessor.h"
//#include <QTextStream>
#include <QDebug>
#include "logconfig.h"
#include "logdatatable.h"
#include <QMap>
#include <QList>

LogProcessor::LogProcessor()
{

}

QList<QString> LogProcessor::spliteByteArray(const QByteArray &arr, const char &a)
{
    QMap<char, char> m;
    m['['] = ']';
    m['{'] = '}';
    m['('] = ')';
    m['"'] = '"';

    auto len = arr.size();
    auto i = 0;
    QList<QString> ans;
    QString t;

    while (i < len) {
        if (arr[i] == a || i == len - 1) {
            ans.push_back(t);
            t.clear();
            ++i;
        }else if (arr[i] == '"' || arr[i] == '{'
                  || arr[i] == '[' || arr[i] == '(') {
            char need = m[arr[i]];
            ++i;
            while (arr[i] != need) {
                t.push_back(arr[i]);
                ++i;
            }
            if (i == len - 1) {
                ans.push_back(t);
                break;
            }
            ++i;
        }else {
            t.push_back(arr[i]);
            ++i;
        }
    }
    return ans;
}

LogProcessor *LogProcessor::getLogProcessor()
{
    static LogProcessor logProcessor;
    qDebug() << "111";
    return &logProcessor;
}

void LogProcessor::start(const QString &path, LogConfig *logConfig, LogDataTable *logDataTable)
{
    QFile file(path);
    qDebug() << "222";
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    qDebug() << "file " << file.exists();

    auto cnt = 0;
    auto delimiter = logConfig->getDelimiter().at(0).unicode();
    auto posToStore = logConfig->getPositionVec();
    qDebug() << "before file for";

    while (!file.atEnd()) {
        QByteArray byteArray = file.readLine();
//        qDebug() << byteArray;
        QList<QString> list = this->spliteByteArray(byteArray, delimiter);
        QList<QString> leftArg;
        for (const auto &t : posToStore) {
            leftArg.push_back(list.at(t - 1));
        }

//        for (const auto &t : leftArg) {
//            qDebug() << t << " | ";
//        }

        logDataTable->addData(leftArg);
        ++cnt;
    }
    qDebug() << "total is " << cnt;
}

