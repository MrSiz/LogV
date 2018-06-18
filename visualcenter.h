#ifndef VISUALCENTER_H
#define VISUALCENTER_H

#include "threadpool.h"


#include <QWidget>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QList>

namespace Ui {
class VisualCenter;
}

class VisualCenter : public QWidget
{
    Q_OBJECT

public:
    explicit VisualCenter(int numThread = 2, QWidget *parent = 0);
    ~VisualCenter();
    void init(int num);
public slots:

    void drawpieChart(QList<int> data, QStringList xnames, QString title, int g_pos);
    void drawbarChart(QList<int> data, QStringList xnames, QString title, int g_pos);
    void drawlineChart(QList<int> data, QStringList xnames, QString title, int g_pos);
    void drawhttpMethodAndTimeChart(QMap<int, int> get, QMap<int, int> head, QMap<int, int> post, QMap<int, int> put,
                           QMap<int, int> del, QMap<int, int> trace);
    void drawipAndHttpReq(QMap<QString, QMap<QString, int>> store);
    void drawbrowserIpStatus(QHash<QString, int>, QHash<QString, QHash<QString, int>>,
                         QHash<QString, QHash<QString, QHash<QString, int>>>);

    void drawipAndOs(QMap<QString, int> visitors, QMap<QString, int> hits, QStringList head);
    void recevieSeries( QList<QPair<QString, qreal>> s0,  QList<QPair<QString, qreal>> s1,  QList<QPair<QString, qreal>> s2);

private:
    Ui::VisualCenter *ui;
    QChartView *chartView;
    QList<QChart*> chartList;
    QList<QAbstractSeries*> series;
    QList<QBarSet*> barSet;

    ThreadPool pool;
};

#endif // VISUALCENTER_H
