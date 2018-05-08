#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customtabstyle.h"

#include <QWidget>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    tabWidget = new QTabWidget;
    w1 = new QWidget;
    w2 = new QWidget;

    QLabel *label1 = new QLabel(tr("1"), w1);
    QLabel *lable2 = new QLabel(tr("2"), w2);

    tabWidget->addTab(w1, tr("test1"));
    tabWidget->addTab(w2, tr("test2"));
    tabWidget->setTabPosition(QTabWidget::West);
    tabWidget->tabBar()->setStyle(new CustomTabStyle);

    QHBoxLayout *hBoxLayout = new QHBoxLayout;

    hBoxLayout->addWidget(tabWidget);
    ui->centralWidget->setLayout(hBoxLayout);
}

MainWindow::MainWindow(QWidget *parent, QWidget *w1, QWidget *w2, QWidget *w3) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tabWidget = new QTabWidget;

    tabWidget->addTab(w1, tr("数据"));
    tabWidget->addTab(w2, tr("单列可视化"));
    tabWidget->addTab(w3, tr("关联可视化"));

    tabWidget->setTabPosition(QTabWidget::West);
    tabWidget->tabBar()->setStyle(new CustomTabStyle);

    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(tabWidget);

    ui->centralWidget->setLayout(hBoxLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
