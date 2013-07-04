#ifndef FINDERDIALOG_H
#define FINDERDIALOG_H

/*
*           Copyright 2013 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*/

#include <QDateTime>
#include <QTableWidgetItem>
#include <QMessageBox>

#include "duplicatesfinder.h"
#include "textformatter.h"
#include "directorytree.h"

namespace Ui {
class FinderDialog;
}

//! Main dialog for search classes [singleton]
class FinderDialog : public QDialog
{
    Q_OBJECT
    
public slots:
    void SetPath(QString path);
    void Duplicates(bool value);

public:
    explicit FinderDialog();
    ~FinderDialog();

    //FinderDialog is singleton
    FinderDialog(FinderDialog const&);   // Don't Implement
    void operator=(FinderDialog const&); // Don't implement
    static FinderDialog& getInstance()
    {
        static FinderDialog instance;
        return instance;
    }
    
private slots:
    void on_pbSearch_clicked();

    void on_cbDuplicatesEnbl_clicked(bool checked);

    void on_pbSelectAll_clicked();

    void on_pbUnselectAll_clicked();

    void on_twFileList_itemChanged(QTableWidgetItem *item);

    void on_pbDeleteSelected_clicked();

    void on_tbDrives_clicked();

    void on_cbSha1_clicked(bool checked);

    void UpdateView();

private:
    QThread *filesFinderThread;
    FilesFinder *filesFinder;

    QThread *duplicatesFinderThread;
    DuplicatesFinder *duplicatesFinder;

    DirectoryTree *dirTree;
    QList<FileInfoEx> *fileList;

    Ui::FinderDialog *ui;

    //! colors of rows
    QColor colorsSet[2];
    //! total size of selected files
    qint64 size;
    //! true when updating view
    bool working;
};

#endif // FINDERDIALOG_H
