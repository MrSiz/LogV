#ifndef VISUALCENTER_H
#define VISUALCENTER_H

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
    explicit VisualCenter(QWidget *parent = 0);
    ~VisualCenter();
    void init(int num);
public slots:

    void drawpieChart(QList<int> data, QStringList xnames, QString title, int g_pos);
    void drawbarChart(QList<int> data, QStringList xnames, QString title, int g_pos);
    void drawlineChart(QList<int> data, QStringList xnames, QString title, int g_pos);
    void drawhttpMethodAndTimeChart(QMap<int, int> get, QMap<int, int> head, QMap<int, int> post, QMap<int, int> put,
                           QMap<int, int> del, QMap<int, int> trace);
    void drawipAndHttpReq(QMap<QString, QMap<QString, int>> store);
    void drawbrowserIpStatus(QMap<QString, int>, QMap<QString, QMap<QString, int>>,
                         QMap<QString, QMap<QString, QMap<QString, int>>>);

    void drawipAndOs(QMap<QString, int> visitors, QMap<QString, int> hits, QStringList head);
private:
    Ui::VisualCenter *ui;
    QChartView *chartView;
    QList<QChart*> chartList;
    QList<QAbstractSeries*> series;
    QList<QBarSet*> barSet;
};

#endif // VISUALCENTER_H
