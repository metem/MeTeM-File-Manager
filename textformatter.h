#ifndef TEXTFORMATTER_H
#define TEXTFORMATTER_H

/*
*           Copyright 2012 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*
* Text formatter
*
* METHODS:
*
* static QString SizeFromBytes(qint64 bytes);
* function used to get size of files in user-friendly format
*
* examples:
* 5 B -> 5 B
* 33114 B -> 32.338 KiB
* 42312442 B -> 40,352 MiB
* ...
*
* ADDITIONAL INFO:
* Max unit - TiB.
*
*/

#include <QString>
#include <qmath.h>

class TextFormatter
{
public:
    static QString SizeFromBytes(qint64 bytes);
};

#endif // TEXTFORMATTER_H
