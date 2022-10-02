#include "filemanager.h"

FileManager::FileManager()
{

}

void FileManager::loadAction(QStandardItemModel *model)
{
    QString fileName = QFileDialog::getOpenFileName(Q_NULLPTR, "Загрузить файл", "/", "bin(*.bin)");

    QFile file(fileName);

    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        qint32 n, m;
        stream >> n >> m;

        model->setRowCount(n);
        model->setColumnCount(m);

        for (int i=0; i<n; ++i)
            for (int j=0; j<m; j++)
            {
                QStandardItem *item = new QStandardItem;
                item->read(stream);
                model->setItem(i, j, item);
            }

        file.close();

        emit FileManager::onLoaded();
    }
}

void FileManager::saveAction(QStandardItemModel *model)
{
    QString fileName = QFileDialog::getSaveFileName(Q_NULLPTR, "Сохранить файл", "/", "bin(*.bin)");

    QFile file(fileName);

    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        qint32 n(model->rowCount()), m(model->columnCount());
        stream << n << m;

        for (int i=0; i<n; ++i)
            for (int j=0; j<m; j++)
                model->item(i,j)->write(stream);

        file.close();
    }
}
