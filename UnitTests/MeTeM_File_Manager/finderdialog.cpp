/*
*           Copyright 2013 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*/

#include "finderdialog.h"
#include "ui_finderdialog.h"

FinderDialog::FinderDialog() :
    QDialog(0),

    filesFinderThread(new QThread),
    filesFinder(new FilesFinder()),

    duplicatesFinderThread(new QThread),
    duplicatesFinder(new DuplicatesFinder()),

    dirTree(new DirectoryTree(this)),
    fileList(new QList<FileInfoEx>()),

    ui(new Ui::FinderDialog),
    size(0)

{
    ui->setupUi(this);

    //ui init settings
    ui->twFileList->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    ui->twFileList->setHorizontalHeaderItem(1, new QTableWidgetItem("Path"));
    ui->twFileList->setHorizontalHeaderItem(2, new QTableWidgetItem("Size"));
    ui->twFileList->setHorizontalHeaderItem(3, new QTableWidgetItem("Creation Date"));

    //colorset for rows
    colorsSet[0] = QColor(255,255,255);
    colorsSet[1] = QColor(230,230,230);

    //thread settings
    duplicatesFinder->moveToThread(duplicatesFinderThread);
    connect(duplicatesFinder, SIGNAL(DSearchFinished()), duplicatesFinderThread, SLOT(quit()));
    connect(duplicatesFinderThread, SIGNAL(finished()), this, SLOT(UpdateView()));
    connect(duplicatesFinderThread, SIGNAL(started()), duplicatesFinder, SLOT(Search()));

    connect(duplicatesFinder, SIGNAL(ProgressChanged(int)), ui->progressBar, SLOT(setValue(int)));

    filesFinder->moveToThread(filesFinderThread);
    connect(filesFinder, SIGNAL(FSearchFinished()), filesFinderThread, SLOT(quit()));
    connect(filesFinderThread, SIGNAL(finished()), this, SLOT(UpdateView()));
    connect(filesFinderThread, SIGNAL(started()), filesFinder, SLOT(Search()));
}

FinderDialog::~FinderDialog()
{
    filesFinderThread->terminate();
    duplicatesFinderThread->terminate();

    delete filesFinderThread;
    delete filesFinder;

    delete duplicatesFinderThread;
    delete duplicatesFinder;

    delete dirTree;
    delete fileList;

    delete ui;
}

void FinderDialog::UpdateView()
{
    ui->progressBar->setMaximum(100); //to back from sliding to normal progress bar after files searching
    ui->pbSearch->setText("Search");

    fileList->clear();

    if (ui->cbDuplicatesEnbl->isChecked())
        fileList->append(duplicatesFinder->GetResult());
    else
        fileList->append(filesFinder->GetResult());

    size = 0;
    working = true;
    ui->twFileList->setRowCount(fileList->count());

    QTableWidgetItem *Item;

    if (ui->cbDuplicatesEnbl->isChecked())
    {
        for (int i = 0; i < fileList->count(); i++)
        {
            Item = new QTableWidgetItem((*fileList)[i].fileName());

            if ((i > 0) && ((*fileList)[i-1].GetID() == (*fileList)[i].GetID()))
                Item->setCheckState(Qt::Checked);
            else Item->setCheckState(Qt::Unchecked);


            Item->setFlags(Item->flags() ^ Qt::ItemIsEditable);
            Item->setBackgroundColor(colorsSet[(*fileList)[i].GetID()%2]);

            ui->twFileList->setItem(i, 0, Item);

            Item = new QTableWidgetItem((*fileList)[i].absolutePath());
            Item->setFlags(Item->flags() ^ Qt::ItemIsEditable);
            Item->setBackgroundColor(colorsSet[(*fileList)[i].GetID()%2]);

            ui->twFileList->setItem(i, 1, Item);

            Item = new QTableWidgetItem(QString::number((*fileList)[i].size()) + " bytes");
            Item->setFlags(Item->flags() ^ Qt::ItemIsEditable);
            Item->setBackgroundColor(colorsSet[(*fileList)[i].GetID()%2]);

            ui->twFileList->setItem(i, 2, Item);

            Item = new QTableWidgetItem((*fileList)[i].created().toString("dd.MM.yyyy hh:mm:ss"));
            Item->setFlags(Item->flags() ^ Qt::ItemIsEditable);
            Item->setBackgroundColor(colorsSet[(*fileList)[i].GetID()%2]);

            ui->twFileList->setItem(i, 3, Item);

            Item = new QTableWidgetItem((*fileList)[i].GetSHA1().toHex().data());
            Item->setFlags(Item->flags() ^ Qt::ItemIsEditable);
            Item->setBackgroundColor(colorsSet[(*fileList)[i].GetID()%2]);

            ui->twFileList->setItem(i, 4, Item);
        }
    }
    else
    {
        for (int i = 0; i < fileList->count(); i++)
        {
            Item = new QTableWidgetItem((*fileList)[i].fileName());
            Item->setCheckState(Qt::Unchecked);

            Item->setFlags(Item->flags() ^ Qt::ItemIsEditable);
            Item->setBackgroundColor(colorsSet[i%2]);

            ui->twFileList->setItem(i, 0, Item);

            Item = new QTableWidgetItem((*fileList)[i].absolutePath());
            Item->setFlags(Item->flags() ^ Qt::ItemIsEditable);
            Item->setBackgroundColor(colorsSet[i%2]);

            ui->twFileList->setItem(i, 1, Item);

            Item = new QTableWidgetItem(QString::number((*fileList)[i].size()) + " bytes");
            Item->setFlags(Item->flags() ^ Qt::ItemIsEditable);
            Item->setBackgroundColor(colorsSet[i%2]);

            ui->twFileList->setItem(i, 2, Item);

            Item = new QTableWidgetItem((*fileList)[i].created().toString("dd.MM.yyyy hh:mm:ss"));
            Item->setFlags(Item->flags() ^ Qt::ItemIsEditable);
            Item->setBackgroundColor(colorsSet[i%2]);

            ui->twFileList->setItem(i, 3, Item);
        }
    }

    working = false;
}

void FinderDialog::on_pbSearch_clicked()
{
    if (duplicatesFinderThread->isRunning() || filesFinderThread->isRunning())
    {
        duplicatesFinder->Stop();
        filesFinder->Stop();
    }
    else
    {
        QDir dir(ui->lePath->text());

        if (!dir.exists())
        {
            QMessageBox::warning(this,
                                 tr("Warning"),
                                 tr("The selected directory does not exist."),
                                 QMessageBox::Ok
                                 );
            return;
        }

        if (ui->cbDuplicatesEnbl->isChecked())
        {
            duplicatesFinder->SetDir(dir);

            DuplicatesFinder::Methods mtd = 0;
            if (ui->cbSha1->isChecked()) mtd = mtd | DuplicatesFinder::Sha1;
            if (ui->cbSize->isChecked()) mtd = mtd | DuplicatesFinder::Size;
            if (ui->cbName->isChecked()) mtd = mtd | DuplicatesFinder::Name;

            if (mtd == 0)
            {
                QMessageBox::warning(this, "Warning", "You have to choose at least one of search methods.", QMessageBox::Ok);
                return;
            }
            duplicatesFinder->IncludeSubdirs(ui->cbSubDirs->isChecked());
            duplicatesFinder->SetMethods(mtd);

            duplicatesFinderThread->start();
        }
        else
        {
            ui->progressBar->setMaximum(0); //to make sliding progress bar
            filesFinder->SetDir(dir);
            filesFinder->SetNameFilters(ui->lePattern->text().split(';', QString::SkipEmptyParts));

            filesFinder->IncludeSubdirs(ui->cbSubDirs->isChecked());
            filesFinderThread->start();
        }

        ui->pbSearch->setText("Stop");
    }
}

void FinderDialog::on_twFileList_itemChanged(QTableWidgetItem *item)
{
    if (item->checkState() & Qt::Checked) size += (*fileList)[item->row()].size();
    else if (!working) size -= (*fileList)[item->row()].size();

    ui->lSFS->setText(TextFormatter<qint64>::SizeFromBytes(size));
}

void FinderDialog::on_pbDeleteSelected_clicked()
{
    int ret = QMessageBox::warning(this,
                                   tr("Warning"),
                                   tr("Are you sure that you want to permanently delete the selected files?"),
                                   QMessageBox::Yes
                                   | QMessageBox::Cancel
                                   );

    if (ret == QMessageBox::Yes)
    {
        QFile *file = NULL;
        for (int i = 0; i < ui->twFileList->rowCount(); i++)
            if (ui->twFileList->item(i,0)->checkState() & Qt::Checked)
            {
                file = new QFile(ui->twFileList->item(i,1)->text() + '/' + ui->twFileList->item(i,0)->text());

                if (file->remove())
                {
                    size -= file->size();
                    ui->twFileList->removeRow(i);
                    i--;
                }

                delete file;
            }
        ui->lSFS->setText(TextFormatter<qint64>::SizeFromBytes(size));
    }
}

//Simple UI actions

void FinderDialog::on_tbDrives_clicked()
{
    if (dirTree->exec() == QDialog::Accepted)
        ui->lePath->setText(dirTree->GetSelectedDir().absolutePath());
}

void FinderDialog::on_pbSelectAll_clicked()
{
    for (int i = 0; i < ui->twFileList->rowCount(); i++)
        ui->twFileList->item(i,0)->setCheckState(Qt::Checked);
}

void FinderDialog::on_pbUnselectAll_clicked()
{
    for (int i = 0; i < ui->twFileList->rowCount(); i++)
        ui->twFileList->item(i,0)->setCheckState(Qt::Unchecked);
}

void FinderDialog::on_cbDuplicatesEnbl_clicked(bool checked)
{
    ui->lPattern->setVisible(!checked);
    ui->lePattern->setVisible(!checked);
}

void FinderDialog::on_cbSha1_clicked(bool checked)
{
    if (checked)
    {
        ui->twFileList->insertColumn(4);
        ui->twFileList->setHorizontalHeaderItem(4, new QTableWidgetItem("Sha1"));
    }
    else
    {
        ui->twFileList->removeColumn(4);
    }
}

void FinderDialog::SetPath(QString path)
{
    ui->lePath->setText(path);
}

void FinderDialog::Duplicates(bool value)
{
    ui->cbDuplicatesEnbl->setChecked(value);
    ui->gbMethods->setVisible(value);
    on_cbDuplicatesEnbl_clicked(value);
}
