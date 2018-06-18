#include "worker.h"
#include <QDebug>


Worker::Worker(QObject *parent) : QObject(parent)
{
    qDebug() << "worker " << QThread::currentThreadId();
}

void Worker::prin()
{
    qDebug() << QThread::currentThreadId() << "worker";
}

void Worker::drawbrowserIpStatus(QHash<QString, int> browser, QHash<QString, QHash<QString, int> > ip, QHash<QString, QHash<QString, QHash<QString, int> > > status)
{
    qDebug() <<"i am a workder" << QThread::currentThreadId();
    QList<QPair<QString, qreal>> series2, series1, series0;
    for (auto i = browser.begin(); i !=browser.end(); ++i) {
        auto &val1 = i.key();
        for (auto j = ip[val1].begin(); j != ip[val1].end(); ++j) {
            auto &val2 = j.key();
            auto kk = status[val1][val2];
            for (auto k = kk.begin(); k != kk.end(); ++k) {
//                series2.append(k.key(),k.value());
                series2.append(QPair<QString, qreal>(k.key(), k.value()));
            }
            series1.append(QPair<QString, qreal>(j.key(), j.value()));
        }
        series0.append(QPair<QString, qreal>(i.key(), i.value()));
    }
    qDebug() << "worker";
    emit browserIpStatus(series0, series1, series2);
}
