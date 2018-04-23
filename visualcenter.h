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
private:
    Ui::VisualCenter *ui;
    QChartView *chartView;
    QList<QChart*> chartList;
    QList<QAbstractSeries*> series;
    QList<QBarSet*> barSet;
};

#endif // VISUALCENTER_H
