#ifndef FILEMODEL_H
#define FILEMODEL_H

/*-------------------------------------------------------
         Copyright - GNU GENERAL PUBLIC LICENSE
                Version 3, 29 June 2007

Custom FileModel class for files explorer (-> QTableView)

METHODS:


ADDITIONAL INFO:


TODO:
-

---------------------------------------------------------*/

#include <QFileSystemModel>
#include <QFileIconProvider>

class FileModel : public QFileSystemModel
{
    Q_OBJECT
public:
    explicit FileModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;

private:

signals:
    
public slots:
    
};

#endif // FILEMODEL_H
