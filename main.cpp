#include "mainwindow.h"
//#include "logvisualwidget.h"
#include "logdataviewer.h"
#include "downloader.h"
#include "datareader.h"
#include "visualcenter.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QThread>
//#include <QtCharts/QChartView>
int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    QDesktopWidget *desk = QApplication::desktop();

    Downloader downloader;
    DataReader dataReader;
    QObject::connect(&downloader, SIGNAL(update()), &dataReader, SLOT(getData()));

    LogDataViewer *logDataViewer = new LogDataViewer;
    VisualCenter *visualCenter = new VisualCenter;
    visualCenter->init(dataReader.getAnalysisNum());

    QObject::connect(&dataReader, SIGNAL(pieChart(QList<int>,QStringList,QString,int)), visualCenter,SLOT(drawpieChart(QList<int>,QStringList,QString,int)));
    QObject::connect(&dataReader, SIGNAL(barChart(QList<int>,QStringList,QString,int)), visualCenter,SLOT(drawbarChart(QList<int>,QStringList,QString,int)));
    QObject::connect(&dataReader, SIGNAL(lineChart(QList<int>,QStringList,QString,int)), visualCenter,SLOT(drawlineChart(QList<int>,QStringList,QString,int)));
    QObject::connect(&dataReader, SIGNAL(send(int,int,LogHeaders,DataTable)), logDataViewer, SLOT(fillTableWidget(int,int,LogHeaders,DataTable)));
    dataReader.initData();

    VisualCenter *relatedVisual = new VisualCenter;
    relatedVisual->init(4);

    QObject::connect(&dataReader, SIGNAL(httpMethodAndTimeChart(QMap<int,int>,QMap<int,int>,QMap<int,int>,QMap<int,int>,QMap<int,int>,QMap<int,int>)),
                     relatedVisual, SLOT(drawhttpMethodAndTimeChart(QMap<int,int>,QMap<int,int>,QMap<int,int>,QMap<int,int>,QMap<int,int>,QMap<int,int>)));
    QObject::connect(&dataReader, SIGNAL(ipAndHttpReq(QMap<QString,QMap<QString,int> >)),
                     relatedVisual, SLOT(drawipAndHttpReq(QMap<QString,QMap<QString,int> >)));
    QObject::connect(&dataReader, SIGNAL(browserIpStatus(QMap<QString,int>,QMap<QString,QMap<QString,int> >,QMap<QString,QMap<QString,QMap<QString,int> > >)),
                     relatedVisual, SLOT(drawbrowserIpStatus(QMap<QString,int>,QMap<QString,QMap<QString,int> >,QMap<QString,QMap<QString,QMap<QString,int> > >)));

    QObject::connect(&dataReader, SIGNAL(ipAndOs(QMap<QString,int>,QMap<QString,int>,QStringList)),
                     relatedVisual, SLOT(drawipAndOs(QMap<QString,int>,QMap<QString,int>,QStringList)));
    MainWindow w(nullptr, logDataViewer, visualCenter, relatedVisual);
    w.setMinimumHeight(850);
    w.setMinimumWidth(1400);
    w.move((desk->width() - w.width()) / 2, (desk->height() - w.height()) / 2);

    w.show();

    qDebug() << "main thread id " << QThread::currentThreadId();
    return a.exec();
}
