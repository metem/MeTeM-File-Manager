#ifndef CHARTDOCKWIDGET_H
#define CHARTDOCKWIDGET_H

/*
*           Copyright 2013 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*/

#include <QDockWidget>
#include <QFileSystemModel>

#include "NightCharts/nightcharts.h"

//! View for files chart (using QFileSystemModel)
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
