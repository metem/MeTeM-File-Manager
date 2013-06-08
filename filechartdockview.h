#ifndef CHARTDOCKWIDGET_H
#define CHARTDOCKWIDGET_H

#include <QDockWidget>
#include <QFileSystemModel>

#include "NightCharts/nightcharts.h"

class FileChartDockView : public QDockWidget
{
    Q_OBJECT
public:
    explicit FileChartDockView(QWidget *parent = 0);
    ~FileChartDockView();

    void setModel(QFileSystemModel *model);
    
signals:
    
public slots:

private:
    void paintEvent(QPaintEvent* e);

    QFileSystemModel* model;
};

#endif // CHARTDOCKWIDGET_H
