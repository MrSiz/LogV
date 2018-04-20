#include "logdataviewer.h"
#include "ui_logdataviewer.h"

#include <QDebug>
#include <QTableWidget>

LogDataViewer::LogDataViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogDataViewer),
    tableWidget(new QTableWidget)
{
    tableWidget->setFont(QFont("Helvetica"));
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    auto headerGoods = tableWidget->horizontalHeader();
//    headerGoods->setSortIndicator(0, Qt::AscendingOrder);
//    headerGoods->setSortIndicatorShown(true);
//    headerGoods->set

    auto colHeader = tableWidget->verticalHeader();
    colHeader->setHidden(true);
    colHeader->setFixedWidth(50);

//    headerGoods->

//    tableWidget->verticalHeader()->adjustSize();
    ui->setupUi(this);
    ui->verticalLayout->addWidget(tableWidget);
}

LogDataViewer::~LogDataViewer()
{
    delete ui;
}

void LogDataViewer::fillTableWidget(int row, int col, const QStringList &header, const QQueue<QList<QString>> &data)
{
    tableWidget->clear();


    tableWidget->setRowCount(row);
    tableWidget->setColumnCount(col);

    tableWidget->setHorizontalHeaderLabels(header);
    const QColor color = QColor("#EEDFCC");
    for (auto r = 0; r < row; ++r) {
        for (auto c = 0; c < col; ++c) {
            auto temp = new QTableWidgetItem(data.at(r).at(c));
            temp->setTextAlignment(Qt::AlignHCenter | Qt::AlignBottom);
            tableWidget->setItem(r, c, temp);
            if (r & 1) {
                temp->setBackgroundColor(color);
            }
        }
    }
//    tableWidget->verticalHeader()->resize(200, 10);
   tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
}
