#include "buttonchild.h"

ButtonChild::ButtonChild(QWidget *parent, QString textBtn, QString toolTipBtn)
{
    auto allBCButtons = parent->findChildren<ButtonChild *>();

    setParent(parent);
    setText(textBtn);
    setToolTip(toolTipBtn);

    int moveY=0;
    foreach (auto btn, allBCButtons) {
        moveY+=btn->size().height();
    }
    move(0,moveY);

    auto curFont=font();
    curFont.setPointSize(16);
    setFont(curFont);
    auto policy=QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    setSizePolicy(policy);
    raise();
    QObject::connect(this, &ButtonChild::clicked,
                     this, &ButtonChild::onClick);
    auto size=fontMetrics().size(Qt::TextSingleLine,text());
    size.setWidth(size.width()+7);
    size.setHeight(size.height()+5);
    resize(size);

    auto effect = new QGraphicsOpacityEffect(this);
    effect->setOpacity(0.5);
    setGraphicsEffect(effect);
    setAutoFillBackground(true);
    QObject::connect(this, &ButtonChild::enterEvent,
                     this, &ButtonChild::onMouseEnter);
    QObject::connect(this, &ButtonChild::leaveEvent,
                     this, &ButtonChild::onMouseLeave);
}

void ButtonChild::onMouseEnter(){
    QGraphicsOpacityEffect* effect = qobject_cast<QGraphicsOpacityEffect*>(graphicsEffect());
    effect->setOpacity(1);
    setGraphicsEffect(effect);
};

void ButtonChild::onMouseLeave(){
    QGraphicsOpacityEffect* effect = qobject_cast<QGraphicsOpacityEffect*>(graphicsEffect());
    effect->setOpacity(0.5);
    setGraphicsEffect(effect);
};

void ButtonChild::onClick(){
    //override it
}
