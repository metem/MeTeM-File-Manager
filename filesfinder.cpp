#include "filesfinder.h"

void FilesFinder::SetDir(QString path)
{
    this->dir = QDir(path);
}

void FilesFinder::SetDir(const QDir& dir)
{
    this->dir = QDir(dir);
}

QFileInfoList FilesFinder::Find(bool subDirs, QDir::Filters filters, const QStringList &nameFilters)
{
    QFileInfoList result;
    QStack<QString> stack;
    stack.push(dir.absolutePath());
    while (!stack.isEmpty())
    {
        QString sSubdir = stack.pop();
        QDir subdir(sSubdir);

        result += subdir.entryInfoList(nameFilters, filters);

        if (subDirs)
        {
            QFileInfoList infoEntries = subdir.entryInfoList(QDir::AllDirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
            for (int i = 0; i < infoEntries.size(); i++)
            {
                QFileInfo& item = infoEntries[i];
                stack.push(item.absoluteFilePath());
            }
        }
    }
    return result;
}
