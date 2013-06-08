#ifndef COMPARATORDIALOG_H
#define COMPARATORDIALOG_H

#include <QDialog>

namespace Ui {
class ComparatorDialog;
}

class ComparatorDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ComparatorDialog(QWidget *parent = 0);
    ~ComparatorDialog();
    
private:
    Ui::ComparatorDialog *ui;
};

#endif // COMPARATORDIALOG_H
