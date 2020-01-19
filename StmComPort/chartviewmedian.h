#ifndef CHARTVIEWMEDIAN_H
#define CHARTVIEWMEDIAN_H

#include "chartview.h"
#include "arratvalue.h"

class ChartViewMedian : public ChartView
{
    Q_OBJECT
    int *signalLenAmp;
    QtCharts::QLineSeries *seriesSignalAmp;
    QList <ArrAtValue> valsDelay, valsAmp;
public:
    void addDelayAtFreq(double point, double freq);
    void addAmpAtFreq(double point, double freq);
    void updateSeriesDelay();
    void updateSeriesAmp();
    ChartViewMedian(QWidget *parent=nullptr);
};

#endif // CHARTVIEWMEDIAN_H
