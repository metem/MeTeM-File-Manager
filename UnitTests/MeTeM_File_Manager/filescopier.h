#ifndef FILESCOPIER_H
#define FILESCOPIER_H

#include <QObject>
#include <QMutex>
#include "filesfinder.h"

class FilesCopier : public QObject
{
    Q_OBJECT

public:
    explicit FilesCopier(QObject *parent = 0);
    ~FilesCopier();

signals:
    //! Progress in %
    void progressChanged(int progress);
    void nextFile(QString file);
    void addToLog(QString file);
    void finished();
    
public slots:
    void setSourceFileList(QFileInfoList *fileList) { this->fileList = fileList; }
    void setDestinatonDir(QDir *destinationDir) { this->destinationDir = destinationDir; }
    void setDeleteAfter(bool value) { this->deleteAfter = value; }
    void copy();

    //! Used to stop thread in proper time (as soon as possible)
    void abort()
    {
        mutex.lock();
        _abort = true;
        mutex.unlock();
    }
    
private:
    QFileInfoList *fileList;
    QDir *destinationDir;
    bool deleteAfter;
    FilesFinder *filesFinder;
    /**
     * @brief Process is aborted when @em true
     */
    bool _abort;
    /**
     * @brief Protects access to #_abort
     */
    QMutex mutex;
};

#endif // FILESCOPIER_H
