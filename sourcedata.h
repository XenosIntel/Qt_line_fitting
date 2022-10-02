#ifndef SOURCEDATA_H
#define SOURCEDATA_H

#include <QObject>
#include <QMainWindow>
#include <QVector>
#include <QStandardItemModel>

class SourceData : public QObject
{
    Q_OBJECT

public:
    SourceData(QMainWindow *main);

    void addRow(QString inpX, QString inpY);

    void deleteRow(int pos);

    QStandardItemModel *model;

signals:
    void onChange();

};

#endif // SOURCEDATA_H
