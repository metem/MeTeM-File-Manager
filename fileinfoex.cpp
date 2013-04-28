#include "fileinfoex.h"

FileInfoEx::FileInfoEx(const FileInfoEx & fileinfo) : QFileInfo(fileinfo), fileID(0)
{
    SHA1 = fileinfo.GetSHA1();
    fileID = fileinfo.GetID();
}

void FileInfoEx::CalculateSHA1()
{
    QFile file(this->absoluteFilePath());
    if (file.open(QIODevice::ReadOnly))
    {
        QCryptographicHash sha1Hash(QCryptographicHash::Sha1);

        while (!file.atEnd())
            sha1Hash.addData(file.read(BLOCK_SIZE));
        SHA1 = sha1Hash.result();
    }
}

void FileInfoEx::AddToList(QList<FileInfoEx> &list1, const QFileInfoList &list2)
{
    for (int i = 0; i < list2.size(); i++)
        list1.append(list2[i]);
}

QList<FileInfoEx> FileInfoEx::ConvertList(QFileInfoList &list)
{
    QList<FileInfoEx> result;
    while (list.count())
    {
        result += list[0];
        list.removeFirst();
    }
    return result;
}
