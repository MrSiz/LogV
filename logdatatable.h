#ifndef LOGDATATABLE_H
#define LOGDATATABLE_H

#include <QList>
#include <QString>
#include <QQueue>

using Table = QList<QString>;
using DataTable = QQueue<Table>;

class LogDataTable
{
public:
    ~LogDataTable() = default;
    LogDataTable();


public:
    void addData(const QList<QString> &list);
    void removeData();
//    Debug
    void printData();

private:
    DataTable dataTable;
};

#endif // LOGDATATABLE_H
