#include "downloader.h"
#include <QTimer>
#include <QProcess>


Downloader::Downloader(QObject *parent) :
    QObject(parent),
    timer(new QTimer())
{
    connect(timer, SIGNAL(timeout()), this, SLOT(download()));
}

void Downloader::work()
{
    const int msec = 5e3;
    timer->start(msec);
}

void Downloader::download() const
{
    QProcess::execute("python /home/mrsiz/downloader.py");
    emit update();
}
