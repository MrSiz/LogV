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
//    qDebug() << R"(\nsdrfw\n)";

    QApplication a(argc, argv);
    QDesktopWidget *desk = QApplication::desktop();

//   LogVisualWidget *logVisualWidget = new LogVisualWidget;

//    QList<int> data{1, 2, 3, 4, 5, 6, 7, 8};
//    QStringList str{"a", "b", "c", "d", "e", "f", "g", "h"};
//    QList<double> pos{1.1, 5.0, 3, 4, 3.6, 6.0, 1.0, 8.0};
//    logVisualWidget->drawBarChart(data, str);
//    logVisualWidget->drawPieChart(data, str);
//    logVisualWidget->drawLineChart(pos, data);


//    QList<QString> A{"3", "a"};
//    QList<QString> B{"2", "b"};
//    QQueue<QList<QString>> QQ;
//    QQ.push_back(A);
//    QQ.push_back(B);


//    logDataViewer->fillTableWidget(2, 2, {"digit", "Alpha"}, QQ);



    Downloader downloader;
    DataReader dataReader;
    QObject::connect(&downloader, SIGNAL(update()), &dataReader, SLOT(getData()));

    LogDataViewer *logDataViewer = new LogDataViewer;
    VisualCenter *visualCenter = new VisualCenter;
    visualCenter->init(dataReader.getAnalysisNum());

    QObject::connect(&dataReader, SIGNAL(pieChart(QList<int>,QStringList,QString,int)), visualCenter,SLOT(drawpieChart(QList<int>,QStringList,QString,int)));
    QObject::connect(&dataReader, SIGNAL(barChart(QList<int>,QStringList,QString,int)), visualCenter,SLOT(drawbarChart(QList<int>,QStringList,QString,int)));
    QObject::connect(&dataReader, SIGNAL(lineChart(QList<int>,QStringList,QString,int)), visualCenter,SLOT(drawlineChart(QList<int>,QStringList,QString,int)));
    MainWindow w(nullptr, visualCenter, logDataViewer);

    QObject::connect(&dataReader, SIGNAL(send(int,int,LogHeaders,DataTable)), logDataViewer, SLOT(fillTableWidget(int,int,LogHeaders,DataTable)));
    dataReader.initData();

    w.setMinimumHeight(850);
    w.setMinimumWidth(1400);
    w.move((desk->width() - w.width()) / 2, (desk->height() - w.height()) / 2);

    w.show();

    qDebug() << "main thread id " << QThread::currentThreadId();
    return a.exec();
}
