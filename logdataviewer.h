#ifndef LOGDATAVIEWER_H
#define LOGDATAVIEWER_H

#include <QWidget>
//#include <QTableWidget>
#include <QString>
#include <QQueue>
#include <QList>

class QTableWidget;

namespace Ui {
class LogDataViewer;
}

class LogDataViewer : public QWidget
{
    Q_OBJECT

public:
    explicit LogDataViewer(QWidget *parent = 0);
    ~LogDataViewer();

public slots:
    void fillTableWidget(int row, int col, const QStringList &header, const QQueue<QList<QString>>& data);


private:
    Ui::LogDataViewer *ui;
    QTableWidget *tableWidget;
};

#endif // LOGDATAVIEWER_H