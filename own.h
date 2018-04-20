#ifndef OWN_H
#define OWN_H

//define my own data structure

#include <QList>
#include <QString>
#include <QQueue>
#include <QStringList>

typedef QList<QString> OneRowLog;
typedef QList<QString> OneColLog;
typedef QQueue<OneRowLog> DataTable;
typedef QStringList LogHeaders;

#endif // OWN_H
