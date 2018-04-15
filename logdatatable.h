#ifndef LOGDATATABLE_H
#define LOGDATATABLE_H

#include <QVector>
#include <QString>

using Table = QVector<QString>;
using DataTable = QVector<Table>;

class LogDataTable
{
public:
    ~LogDataTable() = default;
    LogDataTable();
private:
    DataTable dataTable;
};

#endif // LOGDATATABLE_H
