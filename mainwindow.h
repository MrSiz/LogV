#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QWidget;
class QTabWidget;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(QWidget *parent, QWidget *w1, QWidget *w2, QWidget *w3);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget *w1, *w2;
    QTabWidget *tabWidget;
};

#endif // MAINWINDOW_H
