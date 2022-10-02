#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fMan = new FileManager();

    connect(this, &MainWindow::loadAction, fMan, &FileManager::loadAction);
    connect(this, &MainWindow::saveAction, fMan, &FileManager::saveAction);
    connect(fMan, &FileManager::onLoaded, this, &MainWindow::onTableChange);

    data = new SourceData(this);

    connect(data, &SourceData::onChange, this, &MainWindow::onTableChange);

    ui->tableView->setModel(data->model);

    calc = new MnkCalculator(data, ui);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete fMan;
}

void MainWindow::on_LoadAction_triggered()
{
    emit loadAction(data->model);
}

void MainWindow::on_SaveAction_triggered()
{
    emit saveAction(data->model);
}

void MainWindow::on_buttonAdd_clicked()
{
    bool testX, testY;
    testX = testY = true;
    ui->lineEditX->text().toDouble(&testX);
    ui->lineEditY->text().toDouble(&testY);
    if(testX && testY)
    {
        data->addRow(ui->lineEditX->text(), ui->lineEditY->text());
    }
    else
    {
        QMessageBox::information(this, "Ошибка", "Ошибка ввода данных");
    }

    ui->lineEditX->clear();
    ui->lineEditY->clear();
}

void MainWindow::on_buttonRemove_clicked()
{
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();

    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);

        data->deleteRow(index.row());
    }
}

void MainWindow::on_ExitAction_triggered()
{
    MainWindow::close();
}

void MainWindow::onTableChange()
{
    calc->plot();
}

