#include "logconfig.h"
#include <QByteArray>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include <QDebug>

LogConfig::~LogConfig()
{

}

LogConfig::LogConfig()
{

}

QVector<QString> LogConfig::getDetail() const
{
    return this->vec;
}

QString LogConfig::getDelimiter() const
{
    return this->delimiter;
}

LogConfig *LogConfig::getLogConfig()
{
    static LogConfig logConfig;
    return &logConfig;
}

void LogConfig::readConfig()
{
    //read json file
    QFile file("./conf/parse.json");
    qDebug() << file.exists();
    file.open(QIODevice::ReadOnly);
    QByteArray rawData = file.readAll();

    //parse document
    QJsonDocument doc(QJsonDocument::fromJson(rawData));

    auto json = doc.object();


    //store the config info
    delimiter = json["delimiter"].toString();

    auto jsonArray1 = json["position"].toArray();
    auto jsonValue = jsonArray1.last();
    auto vecLength = jsonValue.toInt();
    vec.resize(vecLength + 1);

    QJsonArray jsonArray2 = json["description"].toArray();

    auto jsonArrayLength = jsonArray1.size();

    for (auto i = 0; i < jsonArrayLength; ++i) {
        auto pos = jsonArray1.at(i).toInt();
        auto ele = jsonArray2.at(i).toString();

        vec[pos] = ele;
        qDebug() << pos << ' ' << ele;
    }

//    qDebug("%s", qPrintable(json["delimiter"].toString()));
}
