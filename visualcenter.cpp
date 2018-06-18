#include "visualcenter.h"
#include "ui_visualcenter.h"

#include <QDateTime>
VisualCenter::VisualCenter(int numThread, QWidget *parent) :
    pool(numThread),
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
    qDebug() << "what happend?";
    static bool flag = false;
    static_cast<QLineSeries*>(series[g_pos])->clear();
    auto len = data.size();
    int max_val = -1;
    qDebug() << "len " << len;
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

void VisualCenter::drawhttpMethodAndTimeChart(QMap<int, int> get, QMap<int, int> head, QMap<int, int> post, QMap<int, int> put, QMap<int, int> del, QMap<int, int> trace)
{
    qDebug() << "draw method and time chart";
    static bool flag = false;
    static QScatterSeries *series0 = new QScatterSeries();
    static QScatterSeries *series1 = new QScatterSeries();
    static QScatterSeries *series2 = new QScatterSeries();
    static QScatterSeries *series3 = new QScatterSeries();
    static QScatterSeries *series4 = new QScatterSeries();
    static QScatterSeries *series5 = new QScatterSeries();


    static QValueAxis *xAxis0 = new QValueAxis;
    static QValueAxis *yAxis0 = new QValueAxis;

    if (series0->count() == 0) {
        series0->setName("Get");
        series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        series0->setMarkerSize(15.0);
    }
    if (series1->count() == 0) {
        series1->setName("Head");
        series1->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        series1->setMarkerSize(15.0);
    }
    if (series2->count() == 0) {
        series2->setName("Post");
        series2->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        series2->setMarkerSize(15.0);
    }

    if (series3->count() == 0) {
        series3->setName("Put");
        series3->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        series3->setMarkerSize(15.0);
    }
    if (series4->count() == 0) {
        series4->setName("Delete");
        series4->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        series4->setMarkerSize(15.0);
    }
    if (series5->count() == 0) {
        series5->setName("Trace");
        series5->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        series5->setMarkerSize(15.0);
    }


    auto max_val0 = -1;
    series0->clear();
    for (auto it = get.begin(); it != get.end(); ++it) {
        if (it.value() > max_val0) {
            max_val0 = it.value();
        }
        qDebug() << "get value" << it.value();
        series0->append(it.key() + 0.5, it.value() + 0.5);
    }

    series1->clear();
    for (auto it = head.begin(); it != head.end(); ++it) {
        if (it.value() > max_val0) {
            max_val0 = it.value();
        }
        series1->append(it.key() + 0.5, it.value() + 0.5);
    }

    series2->clear();
    for (auto it = post.begin(); it != post.end(); ++it) {
        if (it.value() > max_val0)  max_val0 = it.value();
        series2->append(it.key() + 0.5, it.value());
    }

    series3->clear();
    for (auto it = put.begin(); it != put.end(); ++it) {
        if (it.value() > max_val0) max_val0 = it.value();
        series3->append(it.key() + 0.5, it.value());
    }

    series4->clear();
    for (auto it = del.begin(); it != del.end(); ++it) {
        if (it.value() > max_val0) max_val0 = it.value();
        series4->append(it.key() + 0.5, it.value());
    }

    series5->clear();
    for (auto it = trace.begin(); it != trace.end(); ++it) {
        if (it.value() > max_val0) max_val0 = it.value();

        series5->append(it.key() + 0.5, it.value());
    }



    if (flag == false) {


        xAxis0->setLabelFormat("%d");
        xAxis0->setRange(0, 24);
        xAxis0->setMinorTickCount(5);
        xAxis0->setTitleText("time");

        yAxis0->setRange(0, max_val0 + 10);
        yAxis0->setLabelFormat("%d");
        yAxis0->setMinorTickCount(5);
        yAxis0->setTitleText("count");
        chartList[0]->setAnimationOptions(QChart::AllAnimations);
        chartList[0]->setTitle("HttpMethod散点图");
        chartList[0]->addSeries(series0);
        chartList[0]->addSeries(series1);
        chartList[0]->addSeries(series2);
        chartList[0]->addSeries(series3);
        chartList[0]->addSeries(series4);
        chartList[0]->addSeries(series5);

        chartList[0]->createDefaultAxes();

        chartList[0]->setAxisX(xAxis0, series0);
        chartList[0]->setAxisY(yAxis0, series0);

        chartList[0]->setAxisX(xAxis0, series1);
        chartList[0]->setAxisY(yAxis0, series1);

        chartList[0]->setAxisX(xAxis0, series2);
        chartList[0]->setAxisY(yAxis0, series2);

        chartList[0]->setAxisX(xAxis0, series3);
        chartList[0]->setAxisY(yAxis0, series3);

        chartList[0]->setAxisX(xAxis0, series4);
        chartList[0]->setAxisY(yAxis0, series4);

        chartList[0]->setAxisX(xAxis0, series5);
        chartList[0]->setAxisY(yAxis0, series5);

//        chartList[0]->add

        flag = true;
    }

}

void VisualCenter::drawipAndHttpReq(QMap<QString, QMap<QString, int> > store)
{
    qDebug() << "draw bar sereiesssssssss";
    qDebug() << store.size();
    static QBarSeries *series = new QBarSeries;
    static QMap<QString, QBarSet*> barset;
    static bool isSetXNames = false;
    static bool flag = false;
    static QBarCategoryAxis *xAxis = new QBarCategoryAxis;
    static QValueAxis *yAxis = new QValueAxis;
    static QStringList names;
    static QStringList ipAddr;

    for (auto it = store.begin(); it != store.end(); ++it) {
        ipAddr.append(it.key());
        if (barset[it.key()] == nullptr) {
            qDebug() << it.key();
            barset[it.key()] = new QBarSet(it.key());
            series->append(barset[it.key()]);
        }

        auto temp = it.value();
        while (barset[it.key()]->count()) {
            barset[it.key()]->remove(0);
        }
        for (auto val = temp.begin(); val != temp.end(); ++val) {

            if (isSetXNames == false) {
                names << val.key();
            }
            qDebug() << "num is " << val.value();
            barset[it.key()]->append(val.value());

        }
        isSetXNames = true;
    }

    if (flag == false) {

        xAxis->append(names);


        chartList[1]->addSeries(series);
        chartList[1]->setTitle("HttpReq比较");
        chartList[1]->createDefaultAxes();
        chartList[1]->setAnimationOptions(QChart::SeriesAnimations);
        yAxis->setLabelFormat("%d");
//        yAxis->setMin(0);
        yAxis->setRange(0, 150);
        chartList[1]->setAxisX(xAxis, series);
        chartList[1]->setAxisY(yAxis, series);
        flag = true;
    }

}

//static QPieSeries s0, s1, s2;

void VisualCenter::drawbrowserIpStatus(QHash<QString, int> browser, QHash<QString, QHash<QString, int> > ip, QHash<QString, QHash<QString, QHash<QString, int> > > status)
{
    qDebug() << "draw complex pie";

    static QPieSeries *series0 = new QPieSeries;
    static QPieSeries *series1 = new QPieSeries;
    static QPieSeries *series2 = new QPieSeries;

    static bool flag = false;
    series0->clear();
    series1->clear();
    series2->clear();

    for (auto i = browser.begin(); i !=browser.end(); ++i) {
        auto &val1 = i.key();
        for (auto j = ip[val1].begin(); j != ip[val1].end(); ++j) {
            auto &val2 = j.key();
            auto kk = status[val1][val2];
            for (auto k = kk.begin(); k != kk.end(); ++k) {
                series2->append(k.key(),k.value());
            }
            series1->append(j.key(), j.value());
        }
        series0->append(i.key(), i.value());
    }
    series0->setLabelsVisible(true);


    if (flag == false) {



        series0->setHoleSize(0.2);
        series1->setHoleSize(0.4);
        series2->setHoleSize(0.6);
        chartList[2]->addSeries(series0);
        chartList[2]->addSeries(series1);
        chartList[2]->addSeries(series2);


        chartList[2]->createDefaultAxes();
        chartList[2]->setAnimationOptions(QChart::AllAnimations);
        chartList[2]->legend()->setVisible(false);
        chartList[2]->setTitle("浏览器关联统计");
        flag = true;
    }

}

void VisualCenter::drawipAndOs(QMap<QString, int> visitors, QMap<QString, int> hits, QStringList head)
{
    qDebug() << "will drawipAndOs";

    static QBarSet *setVistors = new QBarSet("Visitos");
    static QBarSet *setHits = new QBarSet("Hits");
    static QStackedBarSeries *series = new QStackedBarSeries();

    while (setVistors->count()) {
        setVistors->remove(0);
    }
    while (setHits->count()) {
        setHits->remove(0);
    }
    int maxVal = -1;
    for (const auto &ele : head) {
        setVistors->append(visitors[ele]);
        if (visitors[ele] > maxVal)
            maxVal = visitors[ele];
        setHits->append(hits[ele]);
        if (hits[ele] > maxVal)
            maxVal = hits[ele];
    }

    static bool flag = false;

    if (flag == false) {
        series->append(setVistors);
        series->append(setHits);
        chartList[3]->addSeries(series);
        chartList[3]->createDefaultAxes();
        chartList[3]->setTitle("操作系统访问统计");
        chartList[3]->setAnimationOptions(QChart::SeriesAnimations);
        static QBarCategoryAxis *axis = new QBarCategoryAxis();
        static QValueAxis *yaxis = new QValueAxis();

        yaxis->setLabelFormat("%d");
        yaxis->setRange(0, 500);
        axis->append(head);
        chartList[3]->setAxisX(axis, series);
        chartList[3]->setAxisY(yaxis, series);
        chartList[3]->legend()->setVisible(true);
        flag = true;
    }

}

void VisualCenter::recevieSeries( QList<QPair<QString, qreal>> s0,  QList<QPair<QString, qreal>> s1, QList<QPair<QString, qreal>> s2)
{
    static QPieSeries *series0 = new QPieSeries;
    static QPieSeries *series1 = new QPieSeries;
    static QPieSeries *series2 = new QPieSeries;

    static bool flag = false;
    series0->clear();
    series1->clear();
    series2->clear();

//    while (s0.count()) {
//        series1->append(s0.)
//    }
    int l0 = s0.size(), l1 = s1.size(), l2 = s2.size();
    for (int i = 0; i < l0; ++i) {
        series0->append(s0[i].first, s0[i].second);
    }
    for (int i = 0; i < l1; ++i) {
        series1->append(s1[i].first, s1[i].second);
    }
    for (int i = 0; i < l2; ++i) {
        series2->append(s2[i].first, s2[i].second);
    }
    series0->setLabelsVisible(true);
    if (flag == false) {



        series0->setHoleSize(0.2);
        series1->setHoleSize(0.4);
        series2->setHoleSize(0.6);
        chartList[2]->addSeries(series0);
        chartList[2]->addSeries(series1);
        chartList[2]->addSeries(series2);


        chartList[2]->createDefaultAxes();
        chartList[2]->setAnimationOptions(QChart::AllAnimations);
        chartList[2]->legend()->setVisible(false);
        chartList[2]->setTitle("浏览器关联统计");
        flag = true;
    }
}
