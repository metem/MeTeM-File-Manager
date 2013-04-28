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

QList<FileInfoEx> DuplicatesFinder::Find(Methods mtd, bool subDirs)
{
    QFileInfoList lst = FilesFinder::Find(subDirs, QDir::Files | QDir::Hidden | QDir::System);
    QList<FileInfoEx> result = FileInfoEx::ConvertList(lst);
    if (result.count() == 0) return result;

    char counter;

    if (mtd & DuplicatesFinder::Size)
    {
        qSort(result.begin(), result.end(), compareSize);

        counter = 0;
        result[0].SetID(counter);

        for (int i = 1; i < result.size(); i++)
        {
            if (result[i-1].size() != result[i].size()) counter++; //if it isnt duplicate increase number
            result[i].SetID(counter);
        }
    }

    if (mtd & DuplicatesFinder::Name)
    {
        if (mtd & DuplicatesFinder::Size) ReduceList(result);
        if (result.count() == 0) return result;

        qSort(result.begin(), result.end(), compareName);

        counter = 0;
        result[0].SetID(counter);

        for (int i = 1; i < result.size(); i++)
        {
            if (result[i-1].fileName() != result[i].fileName()) counter++; //if it isnt duplicate increase number
            result[i].SetID(counter);
        }
    }

    if (mtd & DuplicatesFinder::Sha1)
    {
        if (mtd != DuplicatesFinder::Sha1) ReduceList(result); //if isnt choosen ONLY sha1 then have to reduce list
        if (result.count() == 0) return result;

        //Get all SHA1 first (later we are using saved values)
        for (int i = 0; i < result.size(); i++) result[i].CalculateSHA1();

        qSort(result.begin(), result.end(), compareSHA1);

        counter = 0;
        result[0].SetID(counter);

        for (int i = 1; i < result.size(); i++)
        {
            if (result[i-1].GetSHA1() != result[i].GetSHA1()) counter++; //if it isnt duplicate increase number
            result[i].SetID(counter);
        }
    }

    ReduceList(result);
    FixID(result);

    return result;
}
