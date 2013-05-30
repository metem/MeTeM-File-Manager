#ifndef FILESFINDER_H
#define FILESFINDER_H

/*-------------------------------------------------------
         Copyright - GNU GENERAL PUBLIC LICENSE
                Version 3, 29 June 2007

FilesFinder

METHODS:

QFileInfoList Find(bool subDirs, QDir::Filters filters, const QStringList &nameFilters = QStringList());
Extended QDir::entryInfoList method that include sub-directories searching.

ADDITIONAL INFO:
-

TODO:
-

---------------------------------------------------------*/

#include <QObject>
#include <QDir>
#include <QStack>

class FilesFinder : public QObject
{
    Q_OBJECT

public slots:
    void SetDir(QString path);
    void SetDir(const QDir& dir);

protected:
    QDir dir;

public:
    FilesFinder(const QDir& dir) : dir(dir){}
    FilesFinder(QString path = ""){ dir = QDir(path); }

    QFileInfoList Find(bool subDirs, QDir::Filters filters, const QStringList &nameFilters = QStringList());
};

#endif // FILESFINDER_H
