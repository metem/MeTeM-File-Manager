#include "filescopier.h"

FilesCopier::FilesCopier(QObject *parent) :
    QObject(parent),
    fileList(0),
    destinationDir(0),
    filesFinder(new FilesFinder()),
    _abort(false)
{
    filesFinder->IncludeSubdirs(true);
    filesFinder->SetDirFilters(QDir::Files | QDir::Hidden | QDir::System | QDir::NoDotAndDotDot);
}

FilesCopier::~FilesCopier()
{
    delete filesFinder;
    delete destinationDir;
    delete fileList;
}

void FilesCopier::copy()
{
    mutex.lock();
    _abort = false;
    mutex.unlock();

    if ((fileList != 0) && (destinationDir != 0) && (fileList->count() > 0) && destinationDir->exists())
    {
        QList<FileInfoEx> list;
        for (int i = 0; i < fileList->count(); i++)
        {
            // Checks if the process should be aborted
            mutex.lock();
            bool abort = _abort;
            mutex.unlock();

            if (abort)
            {
                emit finished();
                return;
            }

            if ((*fileList)[i].isDir())
            {
                filesFinder->SetDir((*fileList)[i].absoluteFilePath());
                filesFinder->Search();
                list.append(filesFinder->GetResult());
            }
            else list.append((*fileList)[i]);
        }

        qint64 total_size = 0;
        qint64 size = 0;
        for (int i = 0; i < list.count(); i++) total_size += list[i].size();

        for (int i = 0; i < list.count(); i++)
        {
            // Checks if the process should be aborted
            mutex.lock();
            bool abort = _abort;
            mutex.unlock();

            if (abort)
            {
                emit finished();
                return;
            }

            QFileInfo dest(list[i].absoluteFilePath().replace(0, fileList->at(0).absolutePath().length(), destinationDir->absolutePath()));
            QDir dir;
            dir.mkpath(dest.absolutePath());

            emit nextFile(list[i].absoluteFilePath());
            if (QFile::copy(list[i].absoluteFilePath(), dest.absoluteFilePath()))
            {
                emit addToLog("Created: " + dest.absoluteFilePath());
                size += list[i].size();

                emit progressChanged((size*100)/total_size);

                list[i].SetID(1);
                //if (deleteAfter) QFile(list[i].absoluteFilePath()).remove();
                // list.removeAt(i);
            }
            else list[i].SetID(0);
        }

        if (deleteAfter == true)
        {
            for (int i = 0; i < list.count(); i++)
            {
                // Checks if the process should be aborted
                mutex.lock();
                bool abort = _abort;
                mutex.unlock();

                if (abort)
                {
                    emit finished();
                    return;
                }

                if (list[i].GetID() == 1)
                {
                    if (QFile::remove(list[i].absoluteFilePath()))
                        emit addToLog("Deleted: " + list[i].absoluteFilePath());
                    else
                        emit addToLog("Can't delete: " + list[i].absoluteFilePath());
                }
            }
        }
    }

    emit finished();
}
