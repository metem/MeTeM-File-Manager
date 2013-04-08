#ifndef FILEINFOEX_H
#define FILEINFOEX_H

#include <QFileInfo>

class FileInfoEx : public QFileInfo
{
private:
    static const qint64 BLOCK_SIZE = 1024*1024;
    QFile* file;
public:
    FileInfoEx() : QFileInfo(){}
    FileInfoEx(const QString & file) : QFileInfo(file){}
    FileInfoEx(const QFile & file) : QFileInfo(file){}
    FileInfoEx(const QDir & dir, const QString & file) : QFileInfo(dir, file){}
    FileInfoEx(const FileInfoEx & fileinfo) : QFileInfo(fileinfo){}

    QByteArray GetSHA1();
};

#endif // FILEINFOEX_H
