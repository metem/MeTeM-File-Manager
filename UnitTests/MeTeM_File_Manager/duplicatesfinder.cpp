/*
*           Copyright 2013 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*/

#include "duplicatesfinder.h"

//comparation methods
bool compareSHA1(const FileInfoEx& a, const FileInfoEx& b)
{
    return a.GetSHA1() < b.GetSHA1();
}

bool compareSize(const FileInfoEx& a, const FileInfoEx& b)
{
    return a.size() < b.size();
}

bool compareName(const FileInfoEx& a, const FileInfoEx& b)
{
    return a.fileName() < b.fileName();
}

bool compareFinalSort(const FileInfoEx& a, const FileInfoEx& b)
{
    if (a.GetID() == b.GetID()) return (a.absolutePath() < b.absolutePath());
    else return (a.GetID() < b.GetID());
}

void DuplicatesFinder::SetMethods(Methods flags)
{
    method = flags;
}

void DuplicatesFinder::ReduceList(QList<FileInfoEx> &list)
{
    bool isDup = false; //previous element is duplicate or not

    for (int i = 1; i < list.size(); i++)
    {
        if (list[i-1].GetID() == list[i].GetID())
        {
            isDup = true;
        }
        else
        {
            if (!isDup) //remove previous element only if isn't marked as duplicate
            {
                list.removeAt(i-1);
                i--; //list size is changed so we need to decrement index
            }
            isDup = false;
        }
    }

    if (!isDup) list.removeLast();
}

void DuplicatesFinder::FixID(QList<FileInfoEx> &list)
{
    if (list.count() == 0) return;

    uint newID = 0;
    uint ID = list[0].GetID();
    for (int i = 0; i < list.size(); i++)
    {
        if (ID == list[i].GetID()) list[i].SetID(newID);
        else
        {
            newID++;
            ID = list[i].GetID();
            list[i].SetID(newID);
        }
    }
}

void DuplicatesFinder::Search()
{
    stop = false;

    FilesFinder::dirFilters = QDir::Files | QDir::Hidden | QDir::System;
    FilesFinder::Search();

    int progress = 0;
    int last_progress;

    uint counter;

    if ((fileList->count() > 0) && (method & DuplicatesFinder::Size))
    {
        emit ProgressChanged(0);
        qSort(fileList->begin(), fileList->end(), compareSize); //we need data sorted by size

        counter = 0;
        last_progress = 0;
        (*fileList)[0].SetID(counter);

        for (int i = 1; (i < fileList->size()) && !stop; i++)
        {
            progress = (i * 100)/fileList->count();
            if (last_progress < progress)
            {
                last_progress = progress;
                emit ProgressChanged(progress);
            }

            if ((*fileList)[i-1].size() != (*fileList)[i].size()) counter++; //if it isnt duplicate increase number
            (*fileList)[i].SetID(counter);
        }
    }

    if ((fileList->count() > 0) && (method & DuplicatesFinder::Name))
    {
        emit ProgressChanged(0);
        if (method & DuplicatesFinder::Size) ReduceList(*fileList);
        qSort(fileList->begin(), fileList->end(), compareName);

        counter = 0;
        last_progress = 0;
        (*fileList)[0].SetID(counter);

        for (int i = 1; (i < fileList->size()) && !stop; i++)
        {
            progress = (i * 100)/fileList->count();
            if (last_progress < progress)
            {
                last_progress = progress;
                emit ProgressChanged(progress);
            }

            if ((*fileList)[i-1].fileName() != (*fileList)[i].fileName()) counter++; //if it isnt duplicate increase number
            (*fileList)[i].SetID(counter);
        }
    }

    if ((fileList->count() > 0) && (method & DuplicatesFinder::Sha1))
    {
        emit ProgressChanged(0);
        if (method != DuplicatesFinder::Sha1) ReduceList(*fileList); //if isnt choosen ONLY sha1 then have to reduce list

        last_progress = 0;

        qint64 total_size = 0;
        qint64 current_size = 0;
        for (int i = 0; i < fileList->size(); i++) total_size += (*fileList)[i].size();


        //Get all SHA1 first (later we are using saved values)
        for (int i = 0; (i < fileList->size()) && !stop; i++)
        {
            current_size += (*fileList)[i].size();
            progress = (current_size * 100)/total_size;
            if (last_progress < progress)
            {
                last_progress = progress;
                emit ProgressChanged(progress);
            }

            (*fileList)[i].CalculateSHA1();
        }

        qSort(fileList->begin(), fileList->end(), compareSHA1);

        counter = 0;
        (*fileList)[0].SetID(counter);

        for (int i = 1; i < fileList->size(); i++)
        {
            if ((*fileList)[i-1].GetSHA1() != (*fileList)[i].GetSHA1()) counter++; //if it isnt duplicate increase number
            (*fileList)[i].SetID(counter);
        }
    }

    ReduceList(*fileList);
    FixID(*fileList);

    qSort(fileList->begin(), fileList->end(), compareFinalSort);
    emit ProgressChanged(100);
    emit DSearchFinished();
}
