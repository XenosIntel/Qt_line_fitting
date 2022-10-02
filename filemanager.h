#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QFileDialog>
#include <QStandardItemModel>

class FileManager : public QObject
{
    Q_OBJECT

public slots:
    void loadAction(QStandardItemModel *model);

    void saveAction(QStandardItemModel *model);

signals:
    void onLoaded();

public:
    FileManager();
};

#endif // FILEMANAGER_H
