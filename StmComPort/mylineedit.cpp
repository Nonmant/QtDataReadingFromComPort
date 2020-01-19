#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget *parent)
{
    this->setParent(parent);
}

QString MyLineEdit::getText(){
    return this->displayText();
}
