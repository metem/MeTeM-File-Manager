#include "textformatter.h"

QString TextFormatter::SizeFromBytes(qint64 bytes)
{
    if (bytes < 1024) return QString::number(bytes) + " B";

    double result = bytes;
    int i = 0;
    while ((result >= 1024) && (i <= 3))
    {
        result /= 1024;
        i++;
    }

    QString unit = "";

    switch (i)
    {
        case 1: unit = "KiB"; break;
        case 2: unit = "MiB"; break;
        case 3: unit = "GiB"; break;
        case 4: unit = "TiB"; break;
    }

    return QString::number(round(result * 1000.0) / 1000.0) + ' ' + unit;
}
