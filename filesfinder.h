#ifndef FILESFINDER_H
#define FILESFINDER_H

/*
*           Copyright 2012 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*/

#include <QDir>
#include <QStack>

#include "fileinfoex.h"

//! Class used for finding files by name pattern
class FilesFinder : public QObject
{
    Q_OBJECT

public slots:
    void SetDir(QString path) { this->dir = QDir(path); }
    void SetDir(const QDir& dir) { this->dir = dir; }
    //! Recursive folder scan
    void IncludeSubdirs(bool value) { this->includeSubdirs = value; }
    void SetDirFilters(QDir::Filters dirFilters) { this->dirFilters = dirFilters; }
    //! You can use ';' separator (e.g. Q*;*.jpg)
    void SetNameFilters(const QStringList& nameFilters) { this->nameFilters = nameFilters; }

    //! Search for files
    /*!
    * \return Use GetResult() after FSearchFinished() signal
    */
    virtual void Search();

    //! Used to stop thread in proper time (as soon as possible)
    void Stop(){ stop = true; }

signals:
    //! Signal emited when searching FILES is finished (prepared to use GetResult())
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
        : dir(dir), includeSubdirs(includeSubdirs), dirFilters(dirFilters), nameFilters(nameFilters), stop(false), fileList(new QList<FileInfoEx>()) {}

    FilesFinder(QString path = "",
                bool includeSubdirs = false,
                QDir::Filters dirFilters = QDir::Files | QDir::Hidden | QDir::System | QDir::Dirs | QDir::NoDotAndDotDot,
                QStringList nameFilters = QStringList())
    : includeSubdirs(includeSubdirs), dirFilters(dirFilters), nameFilters(nameFilters), stop(false), fileList(new QList<FileInfoEx>())
    { dir = QDir(path); }

    ~FilesFinder();

    QList<FileInfoEx>& GetResult();
};

#endif // FILESFINDER_H
