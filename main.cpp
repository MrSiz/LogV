#include "mainwindow.h"
#include "logdataviewer.h"
#include "downloader.h"
#include "datareader.h"
#include "visualcenter.h"
#include "loginwindow.h"
#include "registerwindow.h"
#include "dao.h"
#include "worker.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QThread>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    Dao dao;
    Downloader downloader;
    DataReader dataReader;

    LoginWindow loginWindow(&dao);
    RegisterWindow registerWindow(&dao);

    QDesktopWidget *desk = QApplication::desktop();
    loginWindow.move((desk->width() - loginWindow.width()) / 2, (desk->height() - loginWindow.height()) / 2);
    loginWindow.show();

    QObject::connect(&loginWindow, SIGNAL(enterRegisterWindow()),
                     &registerWindow, SLOT(show()));


    QObject::connect(&loginWindow, SIGNAL(enterMainWindow()), &downloader, SLOT(work()));
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
    QObject::connect(&dataReader, SIGNAL(browserIpStatus(QHash<QString,int>,QHash<QString,QHash<QString,int> >,QHash<QString,QHash<QString,QHash<QString,int> > >)),
                     relatedVisual, SLOT(drawbrowserIpStatus(QHash<QString,int>,QHash<QString,QHash<QString,int> >,QHash<QString,QHash<QString,QHash<QString,int> > >)));
    QObject::connect(&dataReader, SIGNAL(ipAndOs(QMap<QString,int>,QMap<QString,int>,QStringList)),
                     relatedVisual, SLOT(drawipAndOs(QMap<QString,int>,QMap<QString,int>,QStringList)));
    MainWindow w(nullptr, logDataViewer, visualCenter, relatedVisual);
    w.setMinimumHeight(850);
    w.setMinimumWidth(1400);
    w.move((desk->width() - w.width()) / 2, (desk->height() - w.height()) / 2);

//    QThread work;

//    Worker worker;


//    worker.moveToThread(&work);
//    QObject::connect(&dataReader, SIGNAL(browserIpStatus(QHash<QString,int>,QHash<QString,QHash<QString,int> >,QHash<QString,QHash<QString,QHash<QString,int> > >)),
//                     &worker, SLOT(drawbrowserIpStatus(QHash<QString,int>,QHash<QString,QHash<QString,int> >,QHash<QString,QHash<QString,QHash<QString,int> > >)),  Qt::DirectConnection);

////    QObject::connect(&worker, SIGNAL(browserIpStatus(QPieSeries,QPieSeries,QPieSeries)), relatedVisual, SLOT(recevieSeries(QPieSeries,QPieSeries,QPieSeries)));
//    QObject::connect(&worker, SIGNAL(browserIpStatus(QList<QPair<QString,qreal> >,QList<QPair<QString,qreal> >,QList<QPair<QString,qreal> >)),
//                     relatedVisual, SLOT(recevieSeries(QList<QPair<QString,qreal> >,QList<QPair<QString,qreal> >,QList<QPair<QString,qreal> >)));
    QObject::connect(&loginWindow, SIGNAL(enterMainWindow()), &w, SLOT(show()));
//    work.start();

    qDebug() << "main thread id " << QThread::currentThreadId();
    return a.exec();
}
