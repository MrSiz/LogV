#include "logdatatable.h"
#include <QDebug>
LogDataTable::LogDataTable()
{

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
