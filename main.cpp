#include "mainwindow.h"
#include "logcollector.h"
#include "logconfig.h"
#include "logprocessor.h"
#include "logdatatable.h"
#include "mytesta.h"
#include "logvisualwidget.h"
#include "logdataviewer.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
//#include <QtCharts/QChartView>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDesktopWidget *desk = QApplication::desktop();

//    LogCollector *logCollector = LogCollector::getLogCollector();
//    logCollector->start(5000);

//    qDebug() << "test LogConfig";
//        LogConfig *logConfig = LogConfig::getLogConfig();
//    logConfig->readConfig();
//    qDebug() << "test end";


//    qDebug() << "test logDataTable";
//    LogDataTable logDataTable;
//    qDebug() << "test end";


//    qDebug() << "test LogProcessor";
//    LogProcessor *logProcessor = LogProcessor::getLogProcessor();
//    logProcessor->start("/home/mrsiz/my.txt", logConfig, &logDataTable);
//    qDebug() << "test end";


//   logDataTable.printData();
//    QString tt = QString("tst");
//    LogDataTable test(tt);
//    MyTestA aa;

//    QObject::connect(&test, SIGNAL(pleaseDraw(QVector<QString>)), &aa, SLOT(recev(QVector<QString>)));
//    test.classifyData();

//    MainWindow w;
//    w.move((desk->width() - w.width()) / 2, (desk->height() - w.height()) / 2);
//    w.show();

    LogVisualWidget *logVisualWidget = new LogVisualWidget;
//    logVisualWidget->show();
//    qDebug() << "zzzzz";
//    MainWindow w(nullptr, logVisualWidget, nullptr);
//    w.move((desk->width() - w.width()) / 2, (desk->height() - w.height()) / 2);
//    w.show();

    QList<int> data{1, 2, 3, 4, 5, 6, 7, 8};
    QStringList str{"a", "b", "c", "d", "e", "f", "g", "h"};
    QList<double> pos{1.1, 5.0, 3, 4, 3.6, 6.0, 1.0, 8.0};
    logVisualWidget->drawBarChart(data, str);
    logVisualWidget->drawPieChart(data, str);
    logVisualWidget->drawLineChart(pos, data);


    QList<QString> A{"3", "a"};
    QList<QString> B{"2", "b"};
    QQueue<QList<QString>> QQ;
    QQ.push_back(A);
    QQ.push_back(B);

    LogDataViewer *logDataViewer = new LogDataViewer;
    logDataViewer->fillTableWidget(2, 2, {"digit", "Alpha"}, QQ);

    MainWindow w(nullptr, logVisualWidget, logDataViewer);
    w.setMinimumHeight(700);
    w.setMinimumWidth(1000);
    w.move((desk->width() - w.width()) / 2, (desk->height() - w.height()) / 2);

    w.show();
    return a.exec();
}
