#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QHash>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QList>
#include <QThread>
class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    void prin();
signals:
    void browserIpStatus( QList<QPair<QString, qreal>> s0,  QList<QPair<QString, qreal>> s1,  QList<QPair<QString, qreal>> s2);
public slots:
    void drawbrowserIpStatus(QHash<QString, int> browser, QHash<QString, QHash<QString, int> > ip, QHash<QString, QHash<QString, QHash<QString, int> > > status);
};

#endif // WORKER_H
