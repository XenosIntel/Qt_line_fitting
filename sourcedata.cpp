#include "sourcedata.h"

SourceData::SourceData(QMainWindow *main)
{
    model = new QStandardItemModel(0, 2, main);

    model->setHeaderData(0, Qt::Horizontal, "X:");
    model->setHeaderData(1, Qt::Horizontal, "Y:");
}

void SourceData::addRow(QString inpX, QString inpY)
{
    QList<QStandardItem *> temp;

    temp.append(new QStandardItem(inpX));
    temp.append(new QStandardItem(inpY));

    model->appendRow(temp);

    emit onChange();
}

void SourceData::deleteRow(int pos)
{
    model->removeRow(pos);

    emit onChange();
}
