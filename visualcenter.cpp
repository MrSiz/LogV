#include "visualcenter.h"
#include "ui_visualcenter.h"

#include <QDateTime>
VisualCenter::VisualCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualCenter)
{
    ui->setupUi(this);
}

VisualCenter::~VisualCenter()
{
    delete ui;
}

void VisualCenter::init(int num)
{
    if (num == 1)
        this->ui->gridLayout->setColumnMinimumWidth(0, 400);
    if (num >= 2){
         this->ui->gridLayout->setColumnMinimumWidth(0, 550);
         this->ui->gridLayout->setColumnMinimumWidth(1, 550);
    }

    chartList.reserve(num);
    int index = 0;
    if (num & 1) {
        int row = num >> 1;
//                        this->ui->gridLayout->setRowMinimumHeight(0, 1000);
        for (int i = 0; i < row; ++i) {
            this->ui->gridLayout->setRowMinimumHeight(i, 400);
            for (int j = 0; j < 2; ++j) {
//                chartList[index] = new QChart();
                qDebug() << index;
                chartList.push_back(new QChart());
                series.push_back(nullptr);
                barSet.push_back(new QBarSet(""));
                chartView = new QChartView(chartList.at(index));
                chartView->setRenderHint(QPainter::Antialiasing);
//                chartView->resize(1000, 1000);
                this->ui->gridLayout->addWidget(chartView, i, j);

                ++index;
            }
        }
        this->ui->gridLayout->setRowMinimumHeight(row, 400);
        chartList.push_back(new QChart());
        series.push_back(nullptr);
        barSet.push_back(new QBarSet(""));
        chartView = new QChartView(chartList.at(index));
        chartView->setRenderHint(QPainter::Antialiasing);
        this->ui->gridLayout->addWidget(chartView, row, 0);
        ++index;
    }else {
        int row = num >> 1;
        for (int i = 0; i < row; ++i) {
            this->ui->gridLayout->setRowMinimumHeight(i, 400);
            for (int j = 0; j < 2; ++j) {
//                chartList[index] = new QChart();
                qDebug() << index;
                chartList.push_back(new QChart());
                series.push_back(nullptr);
                barSet.push_back(new QBarSet(""));
                chartView = new QChartView(chartList.at(index));
                chartView->setRenderHint(QPainter::Antialiasing);
                this->ui->gridLayout->addWidget(chartView, i, j);
                ++index;
            }
        }
    }
}

void VisualCenter::drawpieChart(QList<int> data, QStringList xnames, QString title, int g_pos)
{
    if (series[g_pos] == nullptr) {
        series[g_pos] = new QPieSeries;
    }

    auto len = data.size();
    static_cast<QPieSeries*>(series[g_pos])->clear();
    for (auto i = 0; i < len; ++i) {
        static_cast<QPieSeries*>(series[g_pos])->append(xnames.at(i), data.at(i));
    }
    static_cast<QPieSeries*>(series[g_pos])->setLabelsVisible(true);
    chartList[g_pos]->addSeries(series[g_pos]);
    chartList[g_pos]->legend()->setVisible(false);
    chartList[g_pos]->setTitle(title);
//    chartList[g_pos]->legend()->setAlignment(Qt::AlignLeft);
    return ;
}

void VisualCenter::drawbarChart(QList<int> data, QStringList xnames, QString title, int g_pos)
{

    if (series[g_pos] == nullptr) {
        series[g_pos] = new QBarSeries;
    }
//    static QBarSet barSet{"count"};
//    auto setCnt = barSet[g_pos].count();
    while (barSet[g_pos]->count() != 0) {
        barSet[g_pos]->remove(0);
    }
    qDebug() << barSet[g_pos]->count();
    auto len = data.length();
    int max_val = -1;
    for (auto i = 0; i < len; ++i) {
//        qDebug() << data.at(i);
        *(barSet[g_pos]) << data.at(i);
        if (max_val < data.at(i))
            max_val = data.at(i);
    }

    if (static_cast<QBarSeries*>(series[g_pos])->count() == 0) {
        qDebug() << title;
        static_cast<QBarSeries*>(series[g_pos])->append(barSet[g_pos]);
        chartList[g_pos]->setTitle(title);
        chartList[g_pos]->addSeries(series[g_pos]);
//        for (int i = 0; i < barSet.count(); ++i) {
//            qDebug() << barSet.at(i);
//        }
        chartList[g_pos]->createDefaultAxes();

//        static QBarCategoryAxis xAxis();
//        xAxis.append(xnames);
//        chartList[g_pos]->setAxisX(&xAxis, series[g_pos]);

//        static QValueAxis yAxis;
//        yAxis.setLabelFormat("%d");
//        yAxis.setRange(0, max_val + 5);

//        chartList[g_pos]->setAxisY(&yAxis);

        QBarCategoryAxis *xAxis = new QBarCategoryAxis(this);
        xAxis->append(xnames);
        chartList[g_pos]->setAxisX(xAxis, series[g_pos]);

        QValueAxis *yAxis = new QValueAxis(this);
        yAxis->setLabelFormat("%d");
        yAxis->setRange(0, max_val + 5);

        chartList[g_pos]->setAxisY(yAxis);

        chartList[g_pos]->legend()->setVisible(false);

    }
}

void VisualCenter::drawlineChart(QList<int> data, QStringList xnames, QString title, int g_pos)
{
    if (series[g_pos] == nullptr) {
        series[g_pos] = new QLineSeries;
        chartList[g_pos]->setTitle(title);

    }
    static bool flag = false;
    static_cast<QLineSeries*>(series[g_pos])->clear();
    auto len = data.size();
    int max_val = -1;
    for (int i = 0; i < len; ++i) {
        QDateTime valid = QLocale("en-Us").toDateTime(xnames[i].simplified(), "d/MMM/yyyy");
        if (max_val < data[i])
            max_val = data[i];
        static_cast<QLineSeries*>(series[g_pos])->append(valid.toMSecsSinceEpoch(), data.at(i));
    }
    qDebug() <<  static_cast<QLineSeries*>(series[g_pos])->count();
    if (flag == false) {
        chartList[g_pos]->addSeries(series[g_pos]);
        chartList[g_pos]->createDefaultAxes();
        chartList[g_pos]->legend()->setVisible(false);

//        static QBarCategoryAxis xAxis;
//        if (xnames.size() > 10)
//        xAxis.append(xnames);


//        chartList[g_pos]->setAxisX(&xAxis, series[g_pos]);
//QDateTimeAxis
        static QDateTimeAxis xAxis;
        xAxis.setFormat("yyyy-MM-dd");
        static QValueAxis yAxis;
        yAxis.setLabelFormat("%d");
        yAxis.setRange(0, max_val + 10);

        chartList[g_pos]->setAxisX(&xAxis, series[g_pos]);
        chartList[g_pos]->setAxisY(&yAxis);
        flag = true;
    }


//    static

    //    if (static_cast<QLineSeries*>(series[g_pos])->count() == 0)
}
