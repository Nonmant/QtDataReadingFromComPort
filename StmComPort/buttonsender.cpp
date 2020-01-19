#include "buttonsender.h"

ButtonSender::ButtonSender
(QString nameIn, QString str2sendIn, QString str2getIn, QString descriptionIn, QString argument, QStringList names, QStringList arguments)
{
str2send=str2sendIn;
str2get=str2getIn;

button=new QPushButton(nameIn);

button->setToolTip(descriptionIn);
button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

QObject::connect(button,SIGNAL(clicked()),this,SLOT(btnClk()));

if(argument.isEmpty()&&arguments.isEmpty())
    return;

if(argument.isEmpty()&&(!arguments.isEmpty())){
    input=new QComboBox();
    for(int i=0;i<names.length();++i){
        qobject_cast<QComboBox*>(input)->insertItem(0,names.at(i),arguments.at(i));
    }
}else{

if(QString("float double").contains(argument,Qt::CaseInsensitive)){
    input=new QLineEdit();
    qobject_cast<QLineEdit*>(input)->setValidator(new QDoubleValidator(1,10,5,input));
}

if(QString("int").contains(argument,Qt::CaseInsensitive)){
    input=new QLineEdit();
    qobject_cast<QLineEdit*>(input)->setValidator(new QIntValidator(1,72000,input));
}

if(QString("bool").contains(argument,Qt::CaseInsensitive)){
    input=new QCheckBox();
}
}
inputTypeName=input->metaObject()->className();
input->setToolTip(descriptionIn);
//qDebug()<<inputTypeName;

}

ButtonSender::~ButtonSender(){};

QString ButtonSender::getArgument(){
if(QString("none").contains(inputTypeName))return "";

if(QString("QLineEdit").contains(inputTypeName)){
    return  qobject_cast<QLineEdit*>(input)->displayText();
}
if(QString("QCheckBox").contains(inputTypeName)){
    return QString("%1").arg(
        qobject_cast<QCheckBox*>(input)->isChecked());
}
if(QString("QComboBox").contains(inputTypeName)){
    return qobject_cast<QComboBox*>(input)->currentData().toString();
}
return "";
}

void ButtonSender::btnClk(){
    auto arg=getArgument();
    auto temp = str2send.arg(arg);
    if(id){
        write2Thread(str2send.arg(arg),str2get.arg(arg),id,arg);
    }else{
        write2Thread(str2send.arg(arg),str2get.arg(arg));
    }
}
