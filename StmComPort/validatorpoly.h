#ifndef VALIDATORPOLY_H
#define VALIDATORPOLY_H

#include <QValidator>

class ValidatorPoly : public QValidator
{
public:
 QValidator::State validate(QString &input, int &pos) const;
};

#endif // VALIDATORPOLY_H
