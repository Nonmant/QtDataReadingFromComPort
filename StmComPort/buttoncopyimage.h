#ifndef BUTTONCOPYIMAGE_H
#define BUTTONCOPYIMAGE_H

#include "buttonchild.h"

#include <QClipboard>

class ButtonCopyImage : public ButtonChild
{
    Q_OBJECT
    void onClick() override;
public:
    ButtonCopyImage(QWidget *parent=nullptr) : ButtonChild(parent, "⎘", "Копировать изображение") {}
};

#endif // BUTTONCOPYIMAGE_H
