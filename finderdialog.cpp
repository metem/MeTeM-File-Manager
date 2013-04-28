#include "finderdialog.h"
#include "ui_finderdialog.h"

FinderDialog::FinderDialog(QWidget *parent)
{
    FinderDialog("",false, parent);
}

FinderDialog::FinderDialog(QString path, bool duplicates, QWidget *parent) :
    QDialog(parent),
    fileList(NULL),
    duplicatesFinder(new DuplicatesFinder(path)),
    ui(new Ui::FinderDialog),
    size(0)
{
    (void)fileList;
    ui->setupUi(this);
    ui->lePath->setText(path);
    ui->lPattern->setVisible(!duplicates);
    ui->lePattern->setVisible(!duplicates);
    ui->cbDuplicatesEnbl->setChecked(duplicates);
    ui->gbMethods->setVisible(duplicates);
    on_cbDuplicatesEnbl_clicked(duplicates);

    ui->twFileList->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    ui->twFileList->setHorizontalHeaderItem(1, new QTableWidgetItem("Path"));
    ui->twFileList->setHorizontalHeaderItem(2, new QTableWidgetItem("Size"));
    ui->twFileList->setHorizontalHeaderItem(3, new QTableWidgetItem("Creation Date"));


    colorsSet[0] = QColor(255,255,255);
    colorsSet[1] = QColor(230,230,230);
}

FinderDialog::~FinderDialog()
{
    delete fileList;
    delete duplicatesFinder;
    delete ui;
}

void FinderDialog::on_progressBar_valueChanged(int value)
{
    (void)value;
    ui->lProgress->setText(ui->progressBar->text());
}

void dbglist(QList<FileInfoEx> &list)
{
    for (int i = 0; i < list.size(); i++)
    {
        qDebug() << list[i].fileName() << " " << (int)list[i].GetID() << " " << list[i].GetSHA1().toHex();
    }
}

void FinderDialog::on_pbSearch_clicked()
{    
    size = 0;
    working = true;
    duplicatesFinder->SetDir(ui->lePath->text());

    if (ui->cbDuplicatesEnbl->isChecked())
    {
        DuplicatesFinder::Methods mtd = 0;
        if (ui->cbSha1->isChecked()) mtd = mtd | DuplicatesFinder::Sha1;
        if (ui->cbSize->isChecked()) mtd = mtd | DuplicatesFinder::Size;
        if (ui->cbName->isChecked()) mtd = mtd | DuplicatesFinder::Name;

        if (mtd == 0)
        {
            QMessageBox::warning(this, "Warning", "You have to choose at least one of search methods.", QMessageBox::Ok);
            return;
        }
        delete fileList;
        fileList = new QList<FileInfoEx>(duplicatesFinder->Find(mtd, ui->cbSubDirs->isChecked()));
        ui->twFileList->setRowCount(fileList->count());

        QTableWidgetItem *Item;

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
    working = false;
}

void FinderDialog::on_cbDuplicatesEnbl_clicked(bool checked)
{
    ui->lPattern->setVisible(!checked);
    ui->lePattern->setVisible(!checked);

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

void FinderDialog::on_twFileList_itemChanged(QTableWidgetItem *item)
{
    if (item->checkState() & Qt::Checked) size += (*fileList)[item->row()].size();
    else if (!working) size -= (*fileList)[item->row()].size();

    ui->lSFS->setText(TextFormatter::SizeFromBytes(size));
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
        for (int i = 0; i < ui->twFileList->rowCount(); i++)
            if (ui->twFileList->item(i,0)->checkState() & Qt::Checked)
            {
                QString file = (*fileList)[i].absoluteFilePath();
                if (QFile::remove(file))
                {
                    ui->twFileList->removeRow(i);
                    size -= (*fileList)[i].size();
                    ui->lSFS->setText(TextFormatter::SizeFromBytes(size));
                }
            }
}