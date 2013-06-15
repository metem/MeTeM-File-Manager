#ifndef ABOUTBOX_H
#define ABOUTBOX_H

#include <QWidget>

namespace Ui {
class AboutBox;
}

class AboutBox : public QWidget
{
    Q_OBJECT
    
public:
    explicit AboutBox(QWidget *parent = 0);

    //AboutBox is singleton
    AboutBox(AboutBox const&);   // Don't Implement
    void operator=(AboutBox const&); // Don't implement
    static AboutBox& getInstance()
    {
        static AboutBox instance;
        return instance;
    }

    ~AboutBox();
    
private:
    Ui::AboutBox *ui;
};

#endif // ABOUTBOX_H
