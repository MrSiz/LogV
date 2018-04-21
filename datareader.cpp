#include "datareader.h"

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <algorithm>

DataReader::DataReader(QObject *parent) :
    QObject(parent),
    descriptions(getHeadFromConfig()),
    validPos(getPosFromConfig()),
    analysisItem(getAnaItemFromConfig()),
    dataPath(getDataPath()),
    delimiter(getDelimiter())
{
//    initData();
}

LogValidPos DataReader::getPosFromConfig()
{
    QFile file("../LogV/conf/parse.json");
    file.open(QIODevice::ReadOnly);

    QJsonDocument doc{QJsonDocument::fromJson(file.readAll())};
    auto json = doc.object();
    auto jsonArray1 = json["position"].toArray();
    LogValidPos temp;

    for (const auto &pos : jsonArray1) {
        qDebug() << pos.toInt();
        temp << pos.toInt();
    }

    return temp;
}

AnalysisItem DataReader::getAnaItemFromConfig()
{
    QFile file("../LogV/conf/parse.json");
    file.open(QIODevice::ReadOnly);

    QJsonDocument doc{QJsonDocument::fromJson(file.readAll())};
    auto json = doc.object();
    auto jsonArray = json["analysis"].toArray();

    AnalysisItem temp;

    for (const auto &val : jsonArray) {
        qDebug() << val.toInt();
        temp << val.toInt();
    }
    return temp;
}

QString DataReader::getDataPath()
{
    QFile file("../LogV/conf/parse.json");
    file.open(QIODevice::ReadOnly);

    QJsonDocument doc{QJsonDocument::fromJson(file.readAll())};

    auto json = doc.object();
    qDebug() << json["log_path"].toString();
    return json["log_path"].toString();
}

char DataReader::getDelimiter()
{
    QFile file("../LogV/conf/parse.json");
    file.open(QIODevice::ReadOnly);

    QJsonDocument doc{QJsonDocument::fromJson(file.readAll())};

    auto json = doc.object();
    qDebug() << json["delimiter"].toString().at(0);
    return json["delimiter"].toString().at(0).unicode();
}

LogHeaders DataReader::getHeadFromConfig()
{
    QFile file("../LogV/conf/parse.json");
    file.open(QIODevice::ReadOnly);

    QJsonDocument doc{QJsonDocument::fromJson(file.readAll())};

    auto json = doc.object();
    auto jsonArray2 = json["description"].toArray();

    LogHeaders temp;

    for (const auto &val : jsonArray2) {
        qDebug() << val.toString();
        temp << val.toString();
    }
    return temp;
}

void DataReader::getData()
{
    qDebug() << "getData from the local text";

    QFile file(dataPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    data.clear();
    while (!file.atEnd()) {
        QByteArray byteArray = file.readLine();
        QList<QString> list = this->spliteByteArray(byteArray, delimiter);
        qDebug() << list.size() << "and " << validPos.size();
        auto maxPos = *std::max_element(validPos.begin(), validPos.end());
        if (list.size() < maxPos)
            continue;

        QList<QString> leftArg;
        for (const auto &t : validPos) {
            leftArg.push_back(list.at(t - 1));
        }
//        qDebug() << leftArg;
        data.push_back(leftArg);
    }
    emit send(data.size(), descriptions.size(), descriptions, data);
}

QList<QString> DataReader::spliteByteArray(const QByteArray &arr, const char &a)
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

void DataReader::initData()
{
    qDebug() << "init ";
    QFile file(dataPath);
    if (!file.exists())
        return ;
    qDebug() << "here now";
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    data.clear();
    auto cnt = 0;
    while (!file.atEnd()) {
        QByteArray byteArray = file.readLine();
        QList<QString> list = this->spliteByteArray(byteArray, delimiter);
         auto maxPos = *std::max_element(validPos.begin(), validPos.end());
        if (list.size() < maxPos)
            continue;
        qDebug() << list;
        QList<QString> leftArg;
        for (const auto &t : validPos) {

            leftArg.push_back(list.at(t - 1));
        }
//        qDebug() << leftArg;
        data.push_back(leftArg);
        ++cnt;
        qDebug() << cnt;
    }
    qDebug() << "will emit signals";
    emit send(data.size(), descriptions.size(), descriptions, data);
}
