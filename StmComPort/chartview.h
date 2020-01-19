#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChartView>
#include <QtCharts>
#include <QClipboard>
#include <QSizePolicy>
#include "buttoncopyimage.h"

class ChartView : public QChartView
{
    Q_OBJECT
public:
    int *signalLen;
    QtCharts::QLineSeries *seriesSignal;
    //ChartView(QWidget *parent):QChartView(parent){}
    ChartView(QWidget *parent=nullptr);

    void setClearOnOverfloat(bool state);

    virtual ~ChartView();
    private:
    bool clearOnOverfloat=true;

    void wheelEvent(QWheelEvent *e);

    private slots:
    void dataOverfloated(int index);
};

#endif // CHARTVIEW_H
