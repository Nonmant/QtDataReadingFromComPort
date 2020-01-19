#include <QVariant>

#ifndef ARRATVALUE_H
#define ARRATVALUE_H


class ArrAtValue
{
    QVariant value;
    QList<QVariant> arr;
public:
    ArrAtValue();
    ArrAtValue(QVariant val);
    ~ArrAtValue();
    bool operator <(const ArrAtValue &b) const;
    void setVal(QVariant val);
    QVariant getVal();
    bool operator <<(QVariant data);
    QVariant get();
};

#endif // ARRATVALUE_H
