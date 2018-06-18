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

    auto colHeader = tableWidget->verticalHeader();
    colHeader->setHidden(true);
    colHeader->setFixedWidth(50);
    ui->setupUi(this);
    ui->verticalLayout->addWidget(tableWidget);
}

LogDataViewer::~LogDataViewer()
{
    delete ui;
}

void LogDataViewer::fillTableWidget(int row, int col, const LogHeaders &header, const DataTable&  data)
{
    if (ui->lineEdit->text().size() == 0) {

        tableWidget->clear();
        qDebug() << "fill Table Widget enter";

        tableWidget->setRowCount(row);
        tableWidget->setColumnCount(col);

        tableWidget->setHorizontalHeaderLabels(header);
        const QColor color = QColor("#EEDFCC");
        for (auto r = 0; r < row; ++r) {

            for (auto c = 0; c < col; ++c) {
                auto temp = new QTableWidgetItem(data.at(row - r - 1).at(c));
                temp->setTextAlignment(Qt::AlignHCenter | Qt::AlignBottom);
                tableWidget->setItem(r, c, temp);
                if (r & 1) {
                    temp->setBackgroundColor(color);
                }
            }
        }
        qDebug() << "end fill viwer";

       tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }

}

void LogDataViewer::on_lineEdit_editingFinished()
{
    QString str = ui->lineEdit->text();

    int r = tableWidget->rowCount();

    if (str.size() == 0) {
        for (int i = 0; i < r; ++i) {
            tableWidget->setRowHidden(i, false);
        }
    }else {
        auto item = tableWidget->findItems(str, Qt::MatchContains);


        for (int i = 0; i < r; ++i) {
            tableWidget->setRowHidden(i, true);
        }

        if (!item.isEmpty()) {
            for (int i = 0; i < item.count(); ++i) {
                tableWidget->setRowHidden(item.at(i)->row(), false);
                qDebug() << "match " << item.at(i)->row();
            }
        }
    }
}
