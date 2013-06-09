#ifndef FILEINFOEX_H
#define FILEINFOEX_H

/*
*           Copyright 2012 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*
* Extended QFileInfo class
*
* METHODS:
*
* void CalculateSHA1();
*
* result is saved in QByteArray SHA1 field
*
* uses BLOCK_SIZE constant to determine amount of data
* which is reading to memory on each iteration. (maximum memory space used by file).
*
* ADDITIONAL INFO:
*
* Used to save results of duplicatesfinder class.
*
* TODO:
* -
*/

#include <QFileInfo>
#include <QCryptographicHash>

class FileInfoEx : public QFileInfo
{
private:
    static const qint64 BLOCK_SIZE = 1024*1024;
    QByteArray SHA1;
    char fileID;

public:
    FileInfoEx() : QFileInfo(), fileID(0){}
    FileInfoEx(const QString & file) : QFileInfo(file), fileID(0){}
    FileInfoEx(const QFile & file) : QFileInfo(file), fileID(0){}
    FileInfoEx(const QDir & dir, const QString & file) : QFileInfo(dir, file), fileID(0){}
    FileInfoEx(const FileInfoEx & fileinfo);
    FileInfoEx(const QFileInfo & fileinfo) : QFileInfo(fileinfo), fileID(0){}

    char GetID() const { return fileID; }
    void SetID(char ID) { fileID = ID; }

    QByteArray GetSHA1() const { return SHA1; }

    void CalculateSHA1();

    static void AddToList(QList<FileInfoEx> &list1, const QFileInfoList &list2);
    static QList<FileInfoEx> ConvertList(QFileInfoList &list);
};

#endif // FILEINFOEX_H
