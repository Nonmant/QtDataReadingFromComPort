#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H
#include <QLineEdit>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    MyLineEdit(QWidget *parent=nullptr);
public:
Q_INVOKABLE QString getText();
};

#endif // MYLINEEDIT_H
