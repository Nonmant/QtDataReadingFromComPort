#ifndef BUTTONCHARTSERIES2FILE_H
#define BUTTONCHARTSERIES2FILE_H

#include "buttonchild.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include "chartview.h"
#include <QTime>

class ButtonChartSeries2File : public ButtonChild
{
    Q_OBJECT
    void onClick() override;
public:
    ButtonChartSeries2File(ChartView *parent=nullptr) : ButtonChild(parent, "💾", "Сохранить точки в файл"){}

};

#endif // BUTTONCHARTSERIES2FILE_H
