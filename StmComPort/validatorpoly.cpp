#include "validatorpoly.h"

QValidator::State ValidatorPoly::validate(QString &input, int &pos) const{
    input = input.replace(QLatin1String(","),QLatin1String("."));
    auto parts=input.split(" ");

    QRegExp expDigit("^[+\\-]?\\b[\\d]*\\b[\\.]?[\\d]+$");
    QRegExp expDigitAlmost("^[+\\-]?(\\b[\\d]*\\b[\\.]?[\\d]*)?$");

    foreach (auto part, parts) {
        if(part.isEmpty()){
            return QValidator::Intermediate;
        }
        //if any substring is not even an uncompleted digit - all string is invalid
        if(!expDigitAlmost.exactMatch(part)){
            return QValidator::Invalid;
        }
        if(!expDigit.exactMatch(part)){
        //if any substring is just an uncompleted digit - all string is intermediate
            return QValidator::Intermediate;
        }
    }
    //all the substrings are completed digits
    return QValidator::Acceptable;
}
