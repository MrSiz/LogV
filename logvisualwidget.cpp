#include "logvisualwidget.h"
#include "ui_logvisualwidget.h"

LogVisualWidget::LogVisualWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogVisualWidget)
{
    ui->setupUi(this);

//    ui->gridLayout->ad
}

LogVisualWidget::~LogVisualWidget()
{
    delete ui;
}
