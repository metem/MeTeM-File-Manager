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

    char newID = 0;
    char ID = list[0].GetID();
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
    delete fileList;

    FilesFinder::dirFilters = QDir::Files | QDir::Hidden | QDir::System;
    FilesFinder::Search();

    fileList = new QList<FileInfoEx>(FilesFinder::GetResult());

    if (fileList->count() > 0)
    {
        int progress = 0;
        char counter;

        if (method & DuplicatesFinder::Size)
        {
            emit ProgressChanged(0);
            qSort(fileList->begin(), fileList->end(), compareSize); //we need data sorted by size

            counter = 0;
            (*fileList)[0].SetID(counter);

            for (int i = 1; (i < fileList->size()) && !stop; i++)
            {
                if ((*fileList)[i-1].size() != (*fileList)[i].size()) counter++; //if it isnt duplicate increase number
                (*fileList)[i].SetID(counter);

                progress = ((i+1) * 100)/fileList->count();
                if ((i * 100)/fileList->count() < progress)
                    emit ProgressChanged(progress);
            }
        }

        if (method & DuplicatesFinder::Name)
        {
            emit ProgressChanged(0);
            if (method & DuplicatesFinder::Size) ReduceList(*fileList);
            if (fileList->count() == 0)
            {
                emit DSearchFinished();
                return;
            }

            qSort(fileList->begin(), fileList->end(), compareName);

            counter = 0;
            (*fileList)[0].SetID(counter);

            for (int i = 1; (i < fileList->size()) && !stop; i++)
            {
                if ((*fileList)[i-1].fileName() != (*fileList)[i].fileName()) counter++; //if it isnt duplicate increase number
                (*fileList)[i].SetID(counter);

                progress = ((i+1) * 100)/fileList->count();
                if ((i * 100)/fileList->count() < progress)
                    emit ProgressChanged(progress);
            }
        }

        if (method & DuplicatesFinder::Sha1)
        {
            emit ProgressChanged(0);
            if (method != DuplicatesFinder::Sha1) ReduceList(*fileList); //if isnt choosen ONLY sha1 then have to reduce list
            if (fileList->count() == 0)
            {
                emit DSearchFinished();
                return;
            }

            //Get all SHA1 first (later we are using saved values)
            for (int i = 0; (i < fileList->size()) && !stop; i++)
            {
                (*fileList)[i].CalculateSHA1();

                progress = ((i+1) * 100)/fileList->count();
                if ((i * 100)/fileList->count() < progress)
                    emit ProgressChanged(progress);
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
        emit DSearchFinished();
    }
}
