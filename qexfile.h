#ifndef QEXFILE_H
#define QEXFILE_H

#include <QFile>

class QExFile : public QFile
{
public:
    QExFile() : QFile(){}
    QExFile(const QFile &file)
    {

    }

    QExFile(const QString &name) : QFile(name){}
    QExFile(const QString &name, QObject *parent) : QFile(name, parent){}
    QExFile(QFilePrivate &dd, QObject *parent) : QFile(dd, parent){}
    QExFile(QObject *parent) : QFile(parent){}

};

#endif // QEXFILE_H
