#ifndef MNKCALCULATOR_H
#define MNKCALCULATOR_H

#include <QVector>
#include <QtMath>
#include "sourcedata.h"
#include "ui_mainwindow.h"

class MnkCalculator
{
public:
    MnkCalculator(SourceData *inpData, Ui::MainWindow *inpUi);

    void plot();

private:
    void getRange();

    void calculate();

    SourceData *data;
    Ui::MainWindow *ui;

    QVector<double> X, Y, lineX, lineY;
    double xMin, xMax, yMin, yMax, a, b;
};

#endif // MNKCALCULATOR_H
