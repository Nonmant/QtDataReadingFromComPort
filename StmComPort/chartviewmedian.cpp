#include "chartviewmedian.h"

ChartViewMedian::ChartViewMedian(QWidget *parent){
    setParent(parent);

    signalLenAmp=signalLen;
    seriesSignalAmp=new QLineSeries(this);
    QPen pen(Qt::blue);
    pen.setWidth(3);
    seriesSignalAmp->setPen(pen);
    chart()->addSeries(seriesSignalAmp);

    chart()->axisY()->setLabelsColor(Qt::darkRed);

    auto axisAmp=new QValueAxis;
    axisAmp->setRange(0, 2048);
    axisAmp->setLabelsColor(Qt::darkBlue);
    seriesSignalAmp->attachAxis(chart()->axisX());

    chart()->addAxis(axisAmp, Qt::AlignRight);
    seriesSignalAmp->attachAxis(axisAmp);

    seriesSignal->setPointsVisible();
    seriesSignalAmp->setPointsVisible();
}

void ChartViewMedian::addDelayAtFreq(double point, double freq){
    bool newFreq=true;
    int index=0;
    for(int i=0; i<valsDelay.length(); ++i) {
        if(valsDelay[i].getVal().toDouble()==freq){
            newFreq=false;
            index=i;
            break;
        }
    }

    if(newFreq){
        index=valsDelay.length();
        valsDelay.append(ArrAtValue(freq));
    }

    valsDelay[index]<<point;

    updateSeriesDelay();
}

void ChartViewMedian::addAmpAtFreq(double point, double freq){
    bool newFreq=true;
    int index=0;
    for(int i=0; i<valsAmp.length(); ++i) {
        if(valsAmp[i].getVal().toDouble()==freq){
            newFreq=false;
            index=i;
            break;
        }
    }

    if(newFreq){
        index=valsAmp.length();
        valsAmp.append(ArrAtValue(freq));
    }

    valsAmp[index]<<point;

    updateSeriesAmp();
}

void ChartViewMedian::updateSeriesDelay(){
    std::sort(valsDelay.begin(), valsDelay.end());
    seriesSignal->clear();
    for(int i=0; i<valsDelay.length(); ++i){
        seriesSignal->append(valsDelay[i].getVal().toReal(),
                             valsDelay[i].get().toReal());
    }
}

void ChartViewMedian::updateSeriesAmp(){
    std::sort(valsAmp.begin(), valsAmp.end());
    seriesSignalAmp->clear();
    for(int i=0; i<valsAmp.length(); ++i){
        seriesSignalAmp->append(valsAmp[i].getVal().toReal(),
                             valsAmp[i].get().toReal());
    }
}
