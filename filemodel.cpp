#include "filemodel.h"

FileModel::FileModel(QObject *parent) :
    QFileSystemModel(parent)
{
}

QVariant FileModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::BackgroundRole)
    {
        if (index.row() % 2)
            return QColor(230,230,230);
        else
            return QColor(Qt::white);
    }

    return QFileSystemModel::data(index, role);
}
