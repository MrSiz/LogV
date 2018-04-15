#include "mainwindow.h"
#include "logcollector.h"
#include "logconfig.h"
#include "logprocessor.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDesktopWidget *desk = QApplication::desktop();

//    LogCollector *logCollector = LogCollector::getLogCollector();
//    logCollector->start(5000);

//    qDebug() << "test LogConfig";
//    LogConfig *logConfig = LogConfig::getLogConfig();
//    logConfig->readConfig();
//    qDebug() << "test end";

    qDebug() << "test LogProcessor";
    LogProcessor *logProcessor = LogProcessor::getLogProcessor();
    logProcessor->start("/home/mrsiz/my.txt");
    qDebug() << "test end";

    MainWindow w;
    w.move((desk->width() - w.width()) / 2, (desk->height() - w.height()) / 2);
    w.show();

    return a.exec();
}
