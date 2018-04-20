#ifndef LOGDATATABLE_H
#define LOGDATATABLE_H

#include <QObject>
#include <QList>
#include <QString>
#include <QQueue>

using Table = QList<QString>;
using DataTable = QQueue<Table>;

class LogDataTable : public QObject
{
     Q_OBJECT
public:
    ~LogDataTable() = default;
    LogDataTable();
    LogDataTable(const QString &);

signals:
    void pleaseDraw(QVector<QString> a);
    void pleaseFillData(int row, int col, const QStringList &header, const QQueue<QList<QString>>& data);

public slots:
    void classifyData();
    void isUpdate(bool update) const;


public:
    void addData(const QList<QString> &list);
    void removeData();
//    Debug
    void printData();



private:
    DataTable dataTable;

};

#endif // LOGDATATABLE_H
