#ifndef FILEINFOEX_H
#define FILEINFOEX_H

/*
*           Copyright 2013 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*/

#include <QFileInfo>
#include <QCryptographicHash>

//! Extended QFileInfo class, used to save results of duplicatesfinder.
/*!
* ADDITIONAL INFO:
*
* It's recommended to use Size flag with Sha1 to reduce list of potential duplicates
* before method start to calculate Sha1.
*/
class FileInfoEx : public QFileInfo
{
private:
    static const qint64 BLOCK_SIZE = 1024*1024;
    QByteArray SHA1;
    uint fileID;

public:
    FileInfoEx() : QFileInfo(), fileID(0){}
    FileInfoEx(const QString & file) : QFileInfo(file), fileID(0){}
    FileInfoEx(const QFile & file) : QFileInfo(file), fileID(0){}
    FileInfoEx(const QDir & dir, const QString & file) : QFileInfo(dir, file), fileID(0){}
    FileInfoEx(const FileInfoEx & fileinfo);
    FileInfoEx(const QFileInfo & fileinfo) : QFileInfo(fileinfo), fileID(0){}

    uint GetID() const { return fileID; }
    void SetID(uint ID) { fileID = ID; }

    QByteArray GetSHA1() const { return SHA1; }

    //! Calculating SHA1 hash for file
    /*!
    * \return result is saved in QByteArray SHA1; accessible through GetSHA1()
    *
    * uses BLOCK_SIZE constant to determine amount of data which is reading to memory
    * on each iteration. (lower -> more disk reads, higher -> more memory usage)
    */
    void CalculateSHA1();

    static void AddToList(QList<FileInfoEx> &list1, const QFileInfoList &list2);
    static QList<FileInfoEx> ConvertList(QFileInfoList &list);
};

#endif // FILEINFOEX_H
