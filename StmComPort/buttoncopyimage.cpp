#include "buttoncopyimage.h"

void ButtonCopyImage::onClick(){
    QClipboard *clipboard = QApplication::clipboard();
    //hide();
    auto allBCButtons = parent()->findChildren<ButtonChild *>();
    foreach (auto btn, allBCButtons) {
        btn->hide();
    }
    clipboard->setPixmap(parentWidget()->grab());
    foreach (auto btn, allBCButtons) {
        btn->show();
    }
}

