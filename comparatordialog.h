#ifndef COMPARATORDIALOG_H
#define COMPARATORDIALOG_H

/*
*           Copyright 2012 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*/

#include <QDialog>
#include <QFileInfo>

namespace Ui {
class ComparatorDialog;
}

class ComparatorDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ComparatorDialog(QFileInfo file1, QFileInfo file2, QWidget *parent = 0);
    ~ComparatorDialog();
    
private:
    Ui::ComparatorDialog *ui;
};

#endif // COMPARATORDIALOG_H
