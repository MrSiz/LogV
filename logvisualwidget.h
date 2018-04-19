#ifndef LOGVISUALWIDGET_H
#define LOGVISUALWIDGET_H

#include <QWidget>

namespace Ui {
class LogVisualWidget;
}

class LogVisualWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogVisualWidget(QWidget *parent = 0);
    ~LogVisualWidget();

private:
    Ui::LogVisualWidget *ui;
};

#endif // LOGVISUALWIDGET_H
