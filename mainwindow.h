#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QStandardItemModel>
#include <QMessageBox>
#include "sourcedata.h"
#include "filemanager.h"
#include "mnkcalculator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void loadAction(QStandardItemModel *model);

    void saveAction(QStandardItemModel *model);

private slots:
    void on_LoadAction_triggered();

    void on_buttonAdd_clicked();

    void on_buttonRemove_clicked();

    void on_SaveAction_triggered();

    void on_ExitAction_triggered();

    void onTableChange();

private:
    Ui::MainWindow *ui;
    FileManager *fMan;
    SourceData *data;
    MnkCalculator *calc;
};
#endif // MAINWINDOW_H
