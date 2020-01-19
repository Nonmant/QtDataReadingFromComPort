#ifndef BUTTONCHILD_H
#define BUTTONCHILD_H

#include <QPushButton>
#include <QApplication>
#include <QSizePolicy>
#include <QFontMetrics>
#include <QGraphicsOpacityEffect>

class ButtonChild : public QPushButton
{
    Q_OBJECT
signals:
    void enterEvent( QEvent* e );
    void leaveEvent( QEvent* e );
public slots:
    void onMouseEnter();
    void onMouseLeave();
    virtual void onClick();
public:
    ButtonChild(QWidget *parent=nullptr,QString textBtn="", QString toolTipBtn="");
};

#endif // BUTTONCHILD_H
