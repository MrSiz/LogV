#include "logvisualwidget.h"
#include "ui_logvisualwidget.h"
#include <QtCharts/QChart>
#include <QtCharts>
//#include <QtCharts/QChartView>
LogVisualWidget::LogVisualWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogVisualWidget)
{
    ui->setupUi(this);


    QBarSet *barSet = new QBarSet("hh");
    *barSet << 1 << 2 << 3;
    QChart *chart0 = new QChart();
    QBarSeries *series0 = new QBarSeries;
    series0->append(barSet);
    chart0->addSeries(series0);
    chart0->setTitle(tr("Simple bar chart"));

    QStringList catagories;
    catagories << "a" << "b" << "c";

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(catagories);
    chart0->createDefaultAxes();
    chart0->setAxisX(axis, series0);

    chart0->legend()->setVisible(true);
    chart0->legend()->setAlignment(Qt::AlignBottom);


    chart[0] = new QChart();

    chartView = new QChartView(chart[0]);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->gridLayout->addWidget(chartView, 1, 0);


//    chartView = new QChartView(chart0);
    chartView = new QChartView(chart0);
    chartView->setRenderHint(QPainter::Antialiasing);


    ui->gridLayout->addWidget(chartView, 1, 1);

    chart[2] = new QChart();

    chartView = new QChartView(chart[2]);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->gridLayout->addWidget(chartView, 2, 0);

    chart[3] = new QChart();
    chartView = new QChartView(chart[3]);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->gridLayout->addWidget(chartView, 2, 1);



}

LogVisualWidget::~LogVisualWidget()
{
    delete ui;
}

void LogVisualWidget::drawBarChart(const QList<int> &data, const QStringList &xnames)
{
    static QBarSeries *series = new QBarSeries();
    static QBarSet *set = new QBarSet("cnt");
    static QBarCategoryAxis * xAxis= new QBarCategoryAxis();
    static QValueAxis *yAxis = new QValueAxis();

    auto maxValue = -1;
    for (const auto &val : data) {
        if (maxValue < val)
            maxValue = val;
        *set << val;
    }
    series->append(set);
    xAxis->append(xnames);

    yAxis->setTitleText("Count");
    yAxis->setLabelFormat("%d");
    yAxis->setRange(0, maxValue + 1);


    chart[0]->addSeries(series);
    chart[0]->createDefaultAxes();
    chart[0]->setAxisX(xAxis, series);
    chart[0]->setAxisY(yAxis);
    chart[0]->legend()->setVisible(false);
}

void LogVisualWidget::drawPieChart(const QList<int> &data, const QStringList &names)
{
    static QPieSeries *series = new QPieSeries();

    auto len = data.size();

    for (auto i = 0; i < len; ++i) {
        series->append(names.at(i), data.at(i));
    }
    chart[2]->addSeries(series);
    chart[2]->legend()->setAlignment(Qt::AlignLeft);
}

void LogVisualWidget::drawLineChart(const QList<double> &xdata, const QList<int> &ydata)
{
    static QLineSeries *series = new QLineSeries();
    series->clear();

    auto len = xdata.size();
    for (auto i = 0; i < len; ++i) {
        series->append(xdata.at(i), ydata.at(i));
    }

    chart[3]->addSeries(series);
    chart[3]->createDefaultAxes();

}
