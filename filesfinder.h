#ifndef FILESFINDER_H
#define FILESFINDER_H

/*
*           Copyright 2012 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*
* FilesFinder
*
* METHODS:
*
* QFileInfoList Find(bool subDirs, QDir::Filters filters, const QStringList &nameFilters = QStringList());
* Extended QDir::entryInfoList method that include sub-directories searching.
*
*/

#include <QObject>
#include <QDir>
#include <QStack>

#include "fileinfoex.h"

class FilesFinder : public QObject
{
    Q_OBJECT

public slots:
    void SetDir(QString path) { this->dir = QDir(path); }
    void SetDir(const QDir& dir) { this->dir = dir; }
    void IncludeSubdirs(bool value) { this->includeSubdirs = value; }
    void SetDirFilters(QDir::Filters dirFilters) { this->dirFilters = dirFilters; }
    void SetNameFilters(const QStringList& nameFilters) { this->nameFilters = nameFilters; }

    virtual void Search();
    void Stop(){ stop = true; }

signals:
    void FSearchFinished();

protected:
    QDir dir;
    bool includeSubdirs;
    QDir::Filters dirFilters;
    QStringList nameFilters;
    bool stop;

    QList<FileInfoEx> *fileList;

public:
    FilesFinder(const QDir& dir,
                bool includeSubdirs = false,
                QDir::Filters dirFilters = QDir::Files | QDir::Hidden | QDir::System | QDir::Dirs | QDir::NoDotAndDotDot,
                QStringList nameFilters = QStringList())
        : dir(dir), includeSubdirs(includeSubdirs), dirFilters(dirFilters), nameFilters(nameFilters), stop(false), fileList(NULL) {}

    FilesFinder(QString path = "",
                bool includeSubdirs = false,
                QDir::Filters dirFilters = QDir::Files | QDir::Hidden | QDir::System | QDir::Dirs | QDir::NoDotAndDotDot,
                QStringList nameFilters = QStringList())
    : includeSubdirs(includeSubdirs), dirFilters(dirFilters), nameFilters(nameFilters), stop(false), fileList(NULL)
    { dir = QDir(path); }

    ~FilesFinder();

    QList<FileInfoEx>& GetResult();
};

#endif // FILESFINDER_H
