#include "buttonsenderpoly.h"

ButtonSenderPoly::ButtonSenderPoly(
        QString nameIn,
        QString str2sendIn,
        QString str2getIn,
        QString descriptionIn):
        ButtonSender(nameIn,str2sendIn,str2getIn,descriptionIn){
 input= new QLineEdit();
 qobject_cast<QLineEdit*>(input)->setValidator(new ValidatorPoly());
 input->setToolTip(descriptionIn);
}

QString ButtonSenderPoly::getArgument(){
    auto parts = qobject_cast<QLineEdit*>(input)->displayText().split(" ", QString::SkipEmptyParts);
    QString ans=QString::number(parts.length())+' '+qobject_cast<QLineEdit*>(input)->displayText();
    return ans;
}

/*
void ButtonSenderPoly::btnClk(){
    auto arg=getArgument();
    if(id){
        write2Thread(str2send.arg(arg),str2get.arg(arg),id,arg);
    }else{
        write2Thread(str2send.arg(arg),str2get.arg(arg));
    }
}
*/
