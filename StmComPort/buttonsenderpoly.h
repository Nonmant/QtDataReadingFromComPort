#ifndef BUTTONSENDERPOLY_H
#define BUTTONSENDERPOLY_H

#include "buttonsender.h"
#include "validatorpoly.h"

class ButtonSenderPoly : public ButtonSender
{
    Q_OBJECT
    QString getArgument();
public:
    explicit ButtonSenderPoly(
            QString nameIn,
            QString str2sendIn,
            QString str2getIn,
            QString descriptionIn);
signals:

public slots:
    //void btnClk();
};

#endif // BUTTONSENDERPOLY_H
