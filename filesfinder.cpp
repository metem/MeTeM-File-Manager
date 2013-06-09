/*
*           Copyright 2012 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*/

#include "filesfinder.h"

FilesFinder::~FilesFinder()
{
    delete fileList;
}

QList<FileInfoEx>& FilesFinder::GetResult()
{
    return *fileList;
}

void FilesFinder::Search()
{
    stop = false;
    fileList = new QList<FileInfoEx>();
    QStack<QString> stack;
    stack.push(dir.absolutePath());

    while (!stack.isEmpty() && !stop)
    {
        QString sSubdir = stack.pop();
        QDir subdir(sSubdir);

        QList<QFileInfo> flist = subdir.entryInfoList(nameFilters, dirFilters);
        fileList->append(FileInfoEx::ConvertList(flist));

        if (includeSubdirs)
        {
            QFileInfoList infoEntries = subdir.entryInfoList(QDir::AllDirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
            for (int i = 0; i < infoEntries.size(); i++)
            {
                QFileInfo& item = infoEntries[i];
                stack.push(item.absoluteFilePath());
            }
        }
    }
    emit FSearchFinished();
}
