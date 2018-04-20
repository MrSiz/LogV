#ifndef LOGVISUALWIDGET_H
#define LOGVISUALWIDGET_H

#include <QWidget>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QString>
#include <QStringList>
namespace Ui {
class LogVisualWidget;
}

class LogVisualWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogVisualWidget(QWidget *parent = 0);
    ~LogVisualWidget();

public slots:
    void drawBarChart(const QList<int> &data, const QStringList &xnames);
    void drawPieChart(const QList<int> &data, const QStringList &names);
    void drawLineChart(const QList<double> &xdata, const QList<int> &ydata);
private:
    Ui::LogVisualWidget *ui;
    QChartView *chartView;
    QChart *chart[4];
};

#endif // LOGVISUALWIDGET_H
