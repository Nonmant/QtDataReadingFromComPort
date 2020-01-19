#include "mycheckbox.h"

MyCheckBox::MyCheckBox(QWidget *parent)
{
    this->setParent(parent);
}

QString MyCheckBox::getChecked(){
    return QString("%1").arg(this->isChecked());
}
