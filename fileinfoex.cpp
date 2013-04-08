#include "fileinfoex.h"
#include <QCryptographicHash>

QByteArray FileInfoEx::GetSHA1()
{
    QFile file(this->absoluteFilePath());
    if (file.open(QIODevice::ReadOnly))
    {
        QCryptographicHash sha1Hash(QCryptographicHash::Sha1);

        while (!file.atEnd())
            sha1Hash.addData(file.read(BLOCK_SIZE));
        return sha1Hash.result();
    }
    return QByteArray();
}
