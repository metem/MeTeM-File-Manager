#ifndef CHARTDOCKWIDGET_H
#define CHARTDOCKWIDGET_H

#include <QDockWidget>
#include <QFileSystemModel>

#include "NightCharts/nightcharts.h"

class ChartDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit ChartDockWidget(QWidget *parent = 0);
    ~ChartDockWidget();

    void setModel(QFileSystemModel *model);
    
signals:
    
public slots:

private:
    void paintEvent(QPaintEvent* e);

    QFileSystemModel* model;

    QColor colorsSet[10];
};

#endif // CHARTDOCKWIDGET_H
