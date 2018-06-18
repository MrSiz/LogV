#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include "dao.h"

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(Dao *arg, QWidget *parent = 0);
    ~RegisterWindow();

private slots:
    void on_pushButton_pressed();

private:
    Ui::RegisterWindow *ui;
    Dao *dao;
};

#endif // REGISTERWINDOW_H
