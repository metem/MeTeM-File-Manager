#ifndef DUPLICATESFINDER_H
#define DUPLICATESFINDER_H

/*
*           Copyright 2012 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*/

#include <QThread>
#include "filesfinder.h"
#include "fileinfoex.h"


//! Class used to find duplicates of files.
/*!
* ADDITIONAL INFO:
*
* It's recommended to use Size flag with Sha1 to reduce list of potential duplicates
* before method start to calculate Sha1.
*/
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
    //! Progress in %
    void ProgressChanged(int progress);
    //! Signal emited when searching DUPLICATES is finished (prepared to use GetResult())
    void DSearchFinished();

public slots:
    void SetMethods(Methods flags);

    //! Search for duplicates
    /*!
    * \return Use GetResult() after DSearchFinished() signal
    *
    * Creating list of duplicates, any of duplicate have the same ID
    * (accesible by GetID() method) starting from 0.
    *
    * Example:
    * ID  File
    * 0   File_1
    * 0   Duplicate_of_file_1
    * 0   Duplicate_of_file_1
    * 1   File_2
    * 1   Duplicate_of_file_2
    * ...
    */
    void Search();

private:
    //! Remove non-duplicates from list
    /*!
    * \return Removing all unique IDs
    */
    void ReduceList(QList<FileInfoEx> &list);
    //! Setting ID starting form 0
    /*!
    * \return List of duplicates with ID in ascending order (form 0)
    */
    void FixID(QList<FileInfoEx> &list);
    //! Searching method
    Methods method;

public:
    DuplicatesFinder(const QDir& dir) : FilesFinder(dir), method(0) {}
    DuplicatesFinder(QString path = "") : FilesFinder(path), method(0) {}
    ~DuplicatesFinder(){}
};

Q_DECLARE_OPERATORS_FOR_FLAGS(DuplicatesFinder::Methods)

#endif // DUPLICATESFINDER_H
