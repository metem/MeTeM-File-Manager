#ifndef MOVEDIALOG_H
#define MOVEDIALOG_H

#include <QAbstractButton>
#include <QDialog>
#include <QThread>
#include <QCloseEvent>
#include "filescopier.h"

namespace Ui {
class MoveDialog;
}

class MoveDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MoveDialog(QFileInfoList *fileList, QDir *destinationDir, bool deleteAfter, QWidget *parent = 0);
    ~MoveDialog();

public slots:
    void addToLog(QString value);
    void finished();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::MoveDialog *ui;

    QThread *fileCopierThread;
    FilesCopier *fileCopier;

protected:
    void closeEvent(QCloseEvent * event);
};

#endif // MOVEDIALOG_H
