#ifndef FINDERDIALOG_H
#define FINDERDIALOG_H

/*-------------------------------------------------------
         Copyright - GNU GENERAL PUBLIC LICENSE
                Version 3, 29 June 2007

UI for files/duplicates finder.

METHODS:

QColor colorsSet[2]; - colors of rows
qint64 size; - size of selected files
bool working; - true when program is searching files

ADDITIONAL INFO:
-

TODO:
-

---------------------------------------------------------*/


#include <QColor>
#include <QDialog>
#include <QDateTime>
#include <QTableWidgetItem>
#include <QMessageBox>

#include "duplicatesfinder.h"
#include "textformatter.h"

#include <QDebug>

namespace Ui {
class FinderDialog;
}

class FinderDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit FinderDialog(QWidget *parent = 0);
    explicit FinderDialog(QString path, bool duplicates, QWidget *parent = 0);

    ~FinderDialog();
    
private slots:
    void on_progressBar_valueChanged(int value);
    void on_pbSearch_clicked();

    void on_cbDuplicatesEnbl_clicked(bool checked);

    void on_pbSelectAll_clicked();

    void on_pbUnselectAll_clicked();

    void on_twFileList_itemChanged(QTableWidgetItem *item);

    void on_pbDeleteSelected_clicked();

private:
    QList<FileInfoEx> *fileList;
    DuplicatesFinder *duplicatesFinder;
    Ui::FinderDialog *ui;
    QColor colorsSet[2];
    qint64 size;
    bool working;
};

#endif // FINDERDIALOG_H
