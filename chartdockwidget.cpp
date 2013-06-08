#include "chartdockwidget.h"

ChartDockWidget::ChartDockWidget(QWidget *parent) :
    QDockWidget(parent), model(NULL)
{
    colorsSet[0] = Qt::yellow;
    colorsSet[1] = Qt::green;
    colorsSet[2] = Qt::cyan;
    colorsSet[3] = QColor(200,10,50);
    colorsSet[4] = Qt::blue;
    colorsSet[5] = QColor(255,204,51);
    colorsSet[6] = QColor(51,255,204);
    colorsSet[7] = QColor(204,51,255);
    colorsSet[8] = QColor(255,102,51);
    colorsSet[9] = QColor(51,128,204);
}

ChartDockWidget::~ChartDockWidget()
{
    delete model;
}

void ChartDockWidget::setModel(QFileSystemModel *model)
{
    this->model = model;
}

void ChartDockWidget::paintEvent(QPaintEvent* e)
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
            if (list.size() == 1) PieChart.addPiece(list[0].suffix(),colorsSet[0], 100);
            else
                for (int i = 0; i < list.size() - 1; i++)
                {
                    if (list[i].suffix() == list[i+1].suffix()) size += list[i].size();
                    else
                    {
                        float percent = 100.0*(size+list[i].size())/totalSize;
                        PieChart.addPiece(list[i].suffix(),colorsSet[colorCounter%10], percent);
                        size = 0;
                        colorCounter++;
                    }
                }

            float percent = 100.0*(size+list.last().size())/totalSize;
            PieChart.addPiece(list.last().suffix(),colorsSet[colorCounter%5], percent);

            PieChart.draw(&painter);
            PieChart.drawLegend(&painter);
        }
    }
}
