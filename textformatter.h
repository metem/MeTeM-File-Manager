#ifndef TEXTFORMATTER_H
#define TEXTFORMATTER_H

/*
*           Copyright 2012 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*/

#include <qmath.h>

//PIMPL (Private IMPLementation) design pattern

//! Used for convert size in bytes to user-friendly format
/*!
* \return examples:
* 5 B -> 5 B
* 33114 B -> 32.338 KiB
* 42312442 B -> 40,352 MiB
*
* ADDITIONAL INFO:
* Max unit - TiB.
*/
template <typename T>
class TextFormatter
{
public:
    static QString SizeFromBytes(T bytes);
};

template <typename T>
class TextFormatterImpl
{
public:
    static QString SizeFromBytes(T bytes);
};

template <typename T>
QString TextFormatter<T>::SizeFromBytes(T bytes)
{
    return TextFormatterImpl<T>::SizeFromBytes(bytes);
}

template <typename T>
QString TextFormatterImpl<T>::SizeFromBytes(T bytes)
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

    return QString::number(qFloor((result * 1000.0)+0.5) / 1000.0) + ' ' + unit;
}

#endif // TEXTFORMATTER_H
