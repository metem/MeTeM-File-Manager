/*
*           Copyright 2012 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*/

#include "filechartdockview.h"

FileChartDockView::FileChartDockView(QWidget *parent) :
    QDockWidget(parent), model(NULL)
{
}

FileChartDockView::~FileChartDockView()
{
    delete model;
}

void FileChartDockView::setModel(QFileSystemModel *model)
{
    this->model = model;
}

void FileChartDockView::paintEvent(QPaintEvent* e)
{
    QDockWidget::paintEvent(e);
    if (model != NULL)
    {
        QDir dir = model->rootDirectory();

        dir.setFilter(QDir::Files | QDir::Hidden | QDir::System | QDir::NoSymLinks);
        dir.setSorting(QDir::Type | QDir::IgnoreCase);

        QFileInfoList list = dir.entryInfoList();

        if (!list.empty())
        {
            QPainter painter;
            painter.begin(this);

            Nightcharts PieChart;
            PieChart.setType(Nightcharts::Pie);//{Histogramm,Pie,DPie};
            PieChart.setLegendType(Nightcharts::Vertical);//{Round,Vertical}

            PieChart.setCords(10,10,this->height()-30,this->height()-30);


            qint64 totalSize = 0;
            for (int i = 0; i < list.size(); ++i) totalSize += list[i].size();

            qint64 size = 0;

            int colorCounter = 0;
            if (list.size() == 1) PieChart.addPiece(list[0].suffix(), 100);
            else
            {
                float percent = 0;
                for (int i = 0; i < list.size() - 1; i++)
                {
                    if (list[i].suffix() == list[i+1].suffix()) size += list[i].size();
                    else
                    {
                        percent = 100.0*(size+list[i].size())/totalSize;
                        PieChart.addPiece(list[i].suffix(), percent);
                        size = 0;
                        colorCounter++;
                    }
                }

                percent = 100.0*(size+list.last().size())/totalSize;
                PieChart.addPiece(list.last().suffix(), percent);
            }

            PieChart.draw(&painter);
            PieChart.drawLegend(&painter);
        }
    }
}
