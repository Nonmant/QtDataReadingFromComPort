#include "arratvalue.h"

ArrAtValue::ArrAtValue(){}

ArrAtValue::ArrAtValue(QVariant val){
    setVal(val);
}

ArrAtValue::~ArrAtValue(){
    arr.clear();
}

bool ArrAtValue::operator <(const ArrAtValue &b) const{
    return this->value<b.value;
}

void ArrAtValue::setVal(QVariant val){
    value=val;
}

bool ArrAtValue::operator <<(QVariant data){
    if(!arr.isEmpty())
        if(data.type()!=arr.first().type())
            return false;
    arr.append(data);
    return true;
}

QVariant ArrAtValue::get(){
    if(arr.isEmpty()) return 0;
    std::sort(arr.begin(), arr.end());
    return arr.at((arr.length()-1)/ 2);
}
QVariant ArrAtValue::getVal(){
    return value;
}
