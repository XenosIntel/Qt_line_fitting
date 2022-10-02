#include "mnkcalculator.h"

MnkCalculator::MnkCalculator(SourceData *inpData, Ui::MainWindow *inpUi) : data(inpData), ui(inpUi), xMin(0), xMax(0), yMin(0), yMax(0)
{
    ui->widget->addGraph();
    ui->widget->graph(0)->setLineStyle(QCPGraph::LineStyle::lsNone);
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, Qt::blue, 5));

    ui->widget->addGraph();
    ui->widget->graph(1)->setPen(QPen(Qt::red, 3));
}

void MnkCalculator::plot()
{
    getRange();

    ui->widget->xAxis->setRange(xMin - qFabs(xMax - xMin) * 0.1, xMax + qFabs(xMax - xMin) * 0.1);
    ui->widget->yAxis->setRange(yMin - qFabs(yMax - yMin) * 0.1, yMax + qFabs(yMax - yMin) * 0.1);

    int rowCount = data->model->rowCount();


    X.clear();
    Y.clear();

    lineX.clear();
    lineY.clear();

    if(rowCount > 0)
    {
        for(int i = 0; i < rowCount; i++)
        {
            X.push_back(data->model->item(i,0)->text().toDouble());
            Y.push_back(data->model->item(i,1)->text().toDouble());
        }
    }

    ui->widget->graph(0)->setData(X,Y);

    calculate();

    ui->widget->graph(1)->setData(lineX, lineY);

    ui->widget->replot();
}

void MnkCalculator::getRange()
{
    int rowCount = data->model->rowCount();

    if(rowCount > 0)
    {
        xMin = yMin = 0;
        xMax = data->model->item(0,0)->text().toDouble();
        yMax = data->model->item(0,1)->text().toDouble();

        for(int i = 0; i < rowCount; i++)
        {
            if(data->model->item(i,0)->text().toDouble() > xMax)
                xMax = data->model->item(i,0)->text().toDouble();

            if(data->model->item(i,1)->text().toDouble() > yMax)
               yMax = data->model->item(i,1)->text().toDouble();
        }

        xMin = xMax;
        yMin = yMax;

        for(int i = 0; i < rowCount; i++)
        {
            if(data->model->item(i,0)->text().toDouble() < xMin)
                xMin = data->model->item(i,0)->text().toDouble();

            if(data->model->item(i,1)->text().toDouble() < yMin)
                yMin = data->model->item(i,1)->text().toDouble();
        }
    }
}

void MnkCalculator::calculate()
{
    double xSum, ySum, xSquareSum, xySum;
    int rCount;
    xSum = ySum = xSquareSum = xySum = 0;

    rCount = data->model->rowCount();

    if(rCount > 0)
    {
        for(int i = 0; i < rCount; i++)
        {
            xSum += data->model->item(i,0)->text().toDouble();
            ySum += data->model->item(i,1)->text().toDouble();

            xSquareSum += qPow(data->model->item(i,0)->text().toDouble(), 2);

            xySum += data->model->item(i,0)->text().toDouble() *
                     data->model->item(i,1)->text().toDouble();
        }

        //1: ySum = a * rowCount + b * xSum
        //2 :xySum = a * xSum + b * xSquared

        //a*rowCount*xSum + b*xSum^2
        //a*xSum*rCount + b*xSquareSum*rCount

        double lTemp = rCount * xSum + qPow(xSum, 2);
        double rTemp = xSum * rCount + xSquareSum * rCount;

        b = rTemp / lTemp;

        //Подставляем b в первое
        //a*rowCount + b*xSum = ySum
        //a*rowCount = ySum - b*xSum
        //a = ySum/rowCount - b*xSum/rowCount

        a = ySum/rCount - (b * xSum) / rCount;

        getRange();

        lineX.push_back(xMin);
        lineX.push_back(xMax);

        lineY.push_back(a + b * xMin);
        lineY.push_back(a + b * xMax);
    }
}
