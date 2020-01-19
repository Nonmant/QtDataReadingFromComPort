#ifndef BUTTONSENDER_H
#define BUTTONSENDER_H

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QSizePolicy>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QCheckBox>
#include <QComboBox>
#include <QStringList>

#include <QMetaObject>

#include <QDebug>

class ButtonSender: public QObject
{
    Q_OBJECT
protected:
    QString str2send, str2get;
    const char *inputTypeName="none";
public:
    int id=0;
    QAbstractButton *button;
    QWidget *input=nullptr;
    ButtonSender(QString nameIn, QString str2sendIn, QString str2getIn, QString descriptionIn="", QString argument="",QStringList names={},QStringList arguments={});
    ~ButtonSender();
    virtual QString getArgument();
signals:
    void write2Thread(QString data, QString ans="", int id=0, QString arg="");
public slots:
    void btnClk();
};

#endif // BUTTONSENDER_H
