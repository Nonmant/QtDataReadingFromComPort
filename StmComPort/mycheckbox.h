#ifndef MYCHECKBOX_H
#define MYCHECKBOX_H

#include <QCheckBox>

class MyCheckBox : public QCheckBox
{
    Q_OBJECT
public:
    MyCheckBox(QWidget *parent=nullptr);
public:
Q_INVOKABLE QString getChecked();
};

#endif // MYCHECKBOX_H
