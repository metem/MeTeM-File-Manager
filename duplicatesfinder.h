#ifndef DUPLICATESFINDER_H
#define DUPLICATESFINDER_H

/*-------------------------------------------------------
         Copyright - GNU GENERAL PUBLIC LICENSE
                Version 3, 29 June 2007

Class used to find duplicates of files.

METHODS:

QList<FileInfoEx> Find(Methods mtd, bool subDirs);

Returns list of duplicates, any of duplicate have the same ID
(accesible by GetID method) starting from 0.

Example:
ID  File
0   File_1
0   Duplicate_of_file_1
0   Duplicate_of_file_1
1   File_2
1   Duplicate_of_file_2
...

ADDITIONAL INFO:

It's recommended to use Size flag with Sha1 to reduce list of potential duplicates
before method start to calculate Sha1.

TODO:

static QList<FileInfoEx> Find(QFile file, Method mtd, bool subDirs);

---------------------------------------------------------*/

#include <QThread>
#include "filesfinder.h"
#include "fileinfoex.h"

class DuplicatesFinder : public FilesFinder
{
    Q_OBJECT

public:
    enum Method
    {
        Name = 0x01,
        Size = 0x02,
        Sha1 = 0x04,
        SizeAndSha1 = Size | Sha1
    };
    Q_DECLARE_FLAGS(Methods, Method)

signals:
    void ProgressChanged(int progress);
    void DSearchFinished();

public slots:
    void SetMethods(Methods flags);
    void Search();

private:
    void ReduceList(QList<FileInfoEx> &list);
    void FixID(QList<FileInfoEx> &list);
    Methods method;

public:
    DuplicatesFinder(const QDir& dir) : FilesFinder(dir), method(0) {}
    DuplicatesFinder(QString path = "") : FilesFinder(path), method(0) {}
    ~DuplicatesFinder(){}
};

Q_DECLARE_OPERATORS_FOR_FLAGS(DuplicatesFinder::Methods)

#endif // DUPLICATESFINDER_H
