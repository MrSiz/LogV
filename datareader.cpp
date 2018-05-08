#include "datareader.h"

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <algorithm>
#include <QRegExp>
#include <QMap>

DataReader::DataReader(QObject *parent) :
    QObject(parent),
    descriptions(getHeadFromConfig()),
    validPos(getPosFromConfig()),
    analysisItem(getAnaItemFromConfig()),
    dataPath(getDataPath()),
    delimiter(getDelimiter())
{
//    emit(analysisItem.size());
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
        qDebug() << val.toString();
        temp << val.toString();
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

OneColLog DataReader::getColLog(int index) const
{
    auto row = data.size();
    auto col = row == 0 ? 0 : data.at(0).size();
    if (col < index) return OneColLog{};
    OneColLog temp;

    for (auto i = 0; i < row; ++i)
        temp.push_back(data.at(i).at(index));
    return temp;
}

void DataReader::process(const OneColLog &colLog, int g_pos)
{
    qDebug() << "Process the columLog";
    auto len = colLog.size();
    if (len == 0) {
       return ;
    }
    auto temp = colLog[0];
    QRegExp rx(R"(^(?:[0-9]{1,3}\.){3}[0-9]{1,3}$)");
    QRegExp httpStatus(R"(^[12345]\d{2}$)");
    QRegExp date(R"(^\d{2}\/[a-zA-Z]{3}\/\d{4}:\d{2}:\d{2}:\d{2})");
    if (rx.indexIn(temp) != -1) {
        qDebug() << temp;
        QMap<QString, int> m;

        for (const auto &val : colLog) {
            ++m[val];
        }
        QVector<QPair<QString, int>> vec;
        for (auto it = m.begin(); it != m.end(); ++it) {

            vec.push_back({it.key(), it.value()});
        }
        std::sort(vec.begin(), vec.end(), [](const QPair<QString, int> &a, const QPair<QString, int> &b) {
            return a.second > b.second;
        });
        QStringList xnames;
        QList<int> data;

        auto num = std::min(6, vec.size());
        for (auto i = 0; i < num; ++i) {
            xnames.push_back(vec[i].first);
            data.push_back(vec[i].second);
        }

        emit pieChart(data, xnames, "ip访问统计", g_pos);
    }else if (httpStatus.indexIn(temp) != -1) {
        qDebug() << temp;

        QPair<QString, int> p1{"1xx", 0};
        QPair<QString, int> p2{"2xx", 0};
        QPair<QString, int> p3{"3xx", 0};
        QPair<QString, int> p4{"4xx", 0};
        QPair<QString, int> p5{"5xx", 0};

        for (const auto &val : colLog) {
//            qDebug() << val;
            switch (val.at(0).unicode()) {
            case '1':
                ++p1.second;
                break;
            case '2':
                ++p2.second;
                break;
            case '3':
                ++p3.second;
                break;
            case '4':
                ++p4.second;
                break;
            case '5':
                ++p5.second;
                break;
            default:
                break;

            }
        }

        QList<int> data;
        data << p1.second << p2.second << p3.second << p4.second << p5.second;
        QStringList xnames;
        xnames << p1.first << p2.first << p3.first << p4.first << p5.first;
        qDebug() << "send signal draw status barchart";
        emit barChart(data, xnames, "Http状态码统计", g_pos);
    }else if (date.indexIn(temp) != -1) {
        qDebug() << temp;

        QMap<QString, int> m;

        for (const auto &val : colLog) {
            ++m[val.mid(0, 11)];
        }

        QStringList xnames;
        QList<int> data;

        for (auto it = m.begin(); it != m.end(); ++it) {
            data.append(it.value());
//            it.key().replace()
            xnames.append(it.key());
        }
        qDebug() << data;
        qDebug() << xnames;
        emit lineChart(data, xnames, "最近访问数统计", g_pos);
    }else if ([&colLog]() ->bool {
//        bool flag = false;
        for (const auto &ele : colLog) {
            if (ele.contains("Mozilla", Qt::CaseInsensitive))
                return true;
        }
         return false;
    }()) {
        qDebug() << "count user agent source";
        QPair<QString, int> chrome{"Chrome", 0}, firefox{"Firefox", 0}, ie{"IE", 0},
        safari{"Safari", 0}, opera{"Opera", 0}, others{"Others", 0};

        for (const auto &ele : colLog) {
            if (ele.contains("Chrome", Qt::CaseInsensitive)) {
                ++chrome.second;
            }else if (ele.contains("Firefox", Qt::CaseInsensitive)) {
                ++firefox.second;
            }else if (ele.contains("Opera", Qt::CaseInsensitive)) {
                ++opera.second;
            }else if (ele.contains("MSIE", Qt::CaseInsensitive)) {
                ++ie.second;
            }else if (ele.contains("SafaRi", Qt::CaseInsensitive)) {
                ++safari.second;
            }else {
                ++others.second;
            }
        }
        QVector<QPair<QString, int>> vec{chrome, firefox, ie,safari, opera, others};
        std::sort(vec.begin(), vec.end(), [](const QPair<QString, int> &a, const QPair<QString, int> &b){return a.second > b.second;});


        QStringList xnames;
        QList<int> data;

        auto num = vec.size();
        qDebug() << vec;
        for (auto i = 0; i < num; ++i) {
            xnames.push_back(vec[i].first);
            data.push_back(vec[i].second);
        }
        qDebug() << "will process browser";
        emit barChart(data, xnames, "浏览器统计", g_pos);
    }
}

void DataReader::TwoDprocess(const OneColLog &log1, const OneColLog &log2, int g_pos)
{
//处理时间与HTTP Method的关系

    QMap<int, int> get, head, post, put, del, trace;
    auto len = log1.size();

    for (int i = 0; i < len; ++i) {
        int duration = (log1[i].at(12).unicode() - '0') * 10 + log1[i].at(13).unicode() - '0';
        qDebug() << duration;
        if (log2[i].contains("GET")) {
            ++get[duration];
        }else if (log2[i].contains("POST")){
            ++post[duration];
        }else if (log2[i].contains("HEAD")) {
            ++head[duration];
        }else if (log2[i].contains("PUT")) {
            ++put[duration];
        }else if (log2[i].contains("DELETE")) {
            ++del[duration];
        }else if (log2[i].contains("TRACE")) {
            ++trace[duration];
        }
    }
    qDebug() << "httpMethodAndTImeChart";
    emit httpMethodAndTimeChart(get, head, post, put, del, trace);
}

void DataReader::processIpAndHttpRequest(const OneColLog &ip, const OneColLog &request)
{
//    QStringList names;

    QMap<QString, QMap<QString, int>> m;

    auto len = ip.size();
    QMap<QString, int> cnt;

    for (const auto &val : ip) {
        ++cnt[val];
    }
    QVector<QPair<QString, int>> vec;
    for ( auto it = cnt.begin(); it != cnt.end(); ++it) {
        vec.push_back(QPair<QString, int>(it.key(), it.value()));
    }
    std::sort(vec.begin(), vec.end(), [](const QPair<QString, int> &a, const QPair<QString, int> &b) {
        return a.second > b.second;
    });
    int min_val = std::min(5, vec.size());
    QMap<QString, bool> m_ip;
    for (auto i = 0; i < min_val; ++i) {
        m_ip[vec[i].first] = true;
    }
    for (auto i = 0; i < len; ++i) {
        if (m_ip[ip.at(i)] == false) continue;
        if (request[i].contains("GET")) {
            ++m[ip.at(i)]["Get"];
        }else if (request[i].contains("POST")){
            ++m[ip.at(i)]["Post"];
        }else if (request[i].contains("HEAD")) {
            ++m[ip.at(i)]["Head"];
        }else if (request[i].contains("PUT")) {
            ++m[ip.at(i)]["Put"];
        }else if (request[i].contains("DELETE")) {
            ++m[ip.at(i)]["Delete"];
        }else if (request[i].contains("TRACE")) {
            ++m[ip.at(i)]["Trace"];
        }
    }
    emit ipAndHttpReq(m);
}

void DataReader::processBrowserIpStatus(const OneColLog &browser, const OneColLog &ip,const OneColLog &status)
{
    QMap<QString, int> browser_cnt;
    QMap<QString, QMap<QString, int>> ip_cnt;
    QMap<QString, QMap<QString, QMap<QString, int>>> status_cnt;

    auto len = browser.length();

    for (auto i = 0; i < len; ++i) {
        const auto &ele = browser[i];
        const auto &tempIp = ip[i];
        const auto &tempS = status[i];
        if (ele.contains("Chrome", Qt::CaseInsensitive)) {
            ++browser_cnt[tr("Chrome")];
            ++ip_cnt[tr("Chrome")][tempIp];
            ++status_cnt[tr("Chrome")][tempIp][tempS];

        }else if (ele.contains("Firefox", Qt::CaseInsensitive)) {
           ++browser_cnt[tr("Firefox")];
            ++ip_cnt[tr("Firefox")][tempIp];
           ++status_cnt[tr("Firefox")][tempIp][tempS];
        }else if (ele.contains("Opera", Qt::CaseInsensitive)) {
           ++browser_cnt[tr("Opera")];
           ++ip_cnt[tr("Opera")][tempIp];
           ++status_cnt[tr("Opera")][tempIp][tempS];
        }else if (ele.contains("MSIE", Qt::CaseInsensitive)) {
           ++browser_cnt[tr("IE")];
            ++ip_cnt[tr("IE")][tempIp];
           ++status_cnt[tr("IE")][tempIp][tempS];
        }else if (ele.contains("SafaRi", Qt::CaseInsensitive)) {
           ++browser_cnt[tr("Safari")];
           ++ip_cnt[tr("Safari")][tempIp];
           ++status_cnt[tr("Safari")][tempIp][tempS];
        }else {
            ++browser_cnt[tr("Other")];
            ++ip_cnt[tr("Other")][tempIp];
            ++status_cnt[tr("Other")][tempIp][tempS];
        }
    }

    qDebug() << "go to draw complex pid chart";
    emit browserIpStatus(browser_cnt, ip_cnt, status_cnt);
}

void DataReader::processIpAndOs(const OneColLog &ip, const OneColLog &userAgent)
{
    int len = ip.size();
    QMap<QString, QMap<QString, bool> > exitIp;
    QMap<QString, int> visitors;
    QMap<QString, int> hits;

    for (int i = 0; i < len; ++i) {
        if (userAgent[i].contains("Windows", Qt::CaseInsensitive)) {
            if (exitIp["Windows"][ip[i]] == 0)
            {
                exitIp["Windows"][ip[i]] = 1;
                ++visitors["Windows"];
                ++hits["Windows"];
            }else {
                ++hits["Windows"];
            }
        }else if (userAgent[i].contains("Linux", Qt::CaseInsensitive)) {
            if (exitIp["Linux"][ip[i]] == 0) {
                exitIp["Linux"][ip[i]] = 1;
                ++visitors["Linux"];
                ++hits["Linux"];
            }else {
                ++hits["Linux"];
            }
        }else if (userAgent[i].contains("Android", Qt::CaseInsensitive)) {
            if (exitIp["Android"][ip[i]] == 0) {
                exitIp["Android"][ip[i]] = 1;
                ++visitors["Android"];
                ++hits["Android"];
            }else {
                ++hits["Android"];
            }
        }else if (userAgent[i].contains("Macintosh", Qt::CaseInsensitive)) {
            if (exitIp["Macintosh"][ip[i]] == 0) {
                exitIp["Macintosh"][ip[i]] = 1;
                ++visitors["Macintosh"];
                ++hits["Macintosh"];
            }else {
                ++hits["Macintosh"];
            }
        }else if (userAgent[i].contains("Iphone", Qt::CaseInsensitive) || userAgent[i].contains("Ipad", Qt::CaseInsensitive)) {
            if (exitIp["Ios"][ip[i]] == 0) {
                exitIp["Ios"][ip[i]] = 1;
                ++visitors["Ios"];
                ++hits["Ios"];
            }else {
                ++hits["Ios"];
            }
        }else {
            if (exitIp["Unknown"][ip[i]] == 0) {
                exitIp["Unknown"][ip[i]] = 1;
                ++visitors["Unknown"];
                ++hits["Unknown"];
            }else {
                ++hits["Unknown"];
            }
        }
    }
    QStringList head;
    head << "Windows" << "Linux" << "Android" << "Macintosh" << "Ios" << "Unknown";
    qDebug() << "please draw ip and os";
    emit ipAndOs(visitors, hits, head);
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
    process(getColLog(0), 0);
    process(getColLog(3), 3);
    process(getColLog(1), 1);
    process(getColLog(6), 2);
    TwoDprocess(getColLog(1), getColLog(2), 0);
    processIpAndHttpRequest(getColLog(0), getColLog(2));
    processBrowserIpStatus(getColLog(6), getColLog(0), getColLog(3));
    processIpAndOs(getColLog(0), getColLog(6));
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
//        qDebug() << list;
        QList<QString> leftArg;
        for (const auto &t : validPos) {

            leftArg.push_back(list.at(t - 1));
        }
//        qDebug() << leftArg;
        data.push_back(leftArg);
        ++cnt;
//        qDebug() << cnt;
    }
    qDebug() << "will emit signals";
    emit send(data.size(), descriptions.size(), descriptions, data);
    process(getColLog(0), 0);
    process(getColLog(3), 3);
    process(getColLog(1), 1);
    process(getColLog(6), 2);
    TwoDprocess(getColLog(1), getColLog(2), 0);
}

int DataReader::getAnalysisNum() const
{
    return analysisItem.size();
}
