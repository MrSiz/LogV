#include "logdatatable.h"
#include <QDebug>
LogDataTable::LogDataTable()
{

}

LogDataTable::LogDataTable(const QString &)
{
    qDebug() << "call this constructor";
    QList<QString> a;
    a.push_back("1");
    a.push_back("a");
    QList<QString> b;
    b.push_back("2");
    b.push_back("b");
    dataTable.push_back(a);
    dataTable.push_back(b);

//    classifyData();
}

void LogDataTable::classifyData()
{
//    QVector<QString> allData(dataTable.size());

    auto row = dataTable.size();
    auto col = row == 0 ? 0 : dataTable[0].size();
    QVector<QString> singleListData;//(row);
    for (auto i = 0; i < col; ++i) {

        for (auto j = 0; j < row; ++j) {
            singleListData.push_back(dataTable.at(j).at(i));
        }
        qDebug() << "i will emit";
        emit pleaseDraw(singleListData);
        singleListData.clear();
//        "end emit";
    }
}

void LogDataTable::addData(const QList<QString> &list)
{
    dataTable.push_back(list);
}

void LogDataTable::removeData()
{
    dataTable.pop_front();
}

void LogDataTable::printData()
{
//    auto length = dataTable.size();
    for (const auto &vec : dataTable) {
        qDebug() << vec;
    }
    return ;
}
