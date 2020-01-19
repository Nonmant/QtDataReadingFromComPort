#include "chartview.h"
#include "buttonchartseries2file.h"
ChartView::ChartView(QWidget *parent)
{
    this->setParent(parent);

    signalLen=new int(800);

    seriesSignal=new QLineSeries(this);
    QPen pen(Qt::red);
    pen.setWidth(3);
    seriesSignal->setPen(pen);

    QChart *chart=new QChart();

    chart->addSeries(seriesSignal);
    chart->createDefaultAxes();
    chart->legend()->setVisible(false);
    this->setChart(chart);

    chart->axisX()->setRange(0,*signalLen);
    chart->axisY()->setRange(-2048, 2048);

    QObject::connect(seriesSignal,&QLineSeries::pointAdded,
                     this, &ChartView::dataOverfloated);

    new ButtonCopyImage(this);
    new ButtonChartSeries2File(this);
}

ChartView::~ChartView() {};

void ChartView::wheelEvent(QWheelEvent *e){
    e->accept();

    if(e->buttons()==Qt::LeftButton){
        return;
    }

    int res=-(100*e->angleDelta().ry())/120;
    if(*signalLen!=10){
        res+=*signalLen;
    }
    if(res<10)
    res=10;
    else if(res>5000){
        res=5000;
    }

    *signalLen=res;
    this->chart()->axisX()->setRange(0,*signalLen);
}

void ChartView::setClearOnOverfloat(bool state){
    if(state==clearOnOverfloat)return;
    clearOnOverfloat=state;
    if(state){
        QObject::connect(seriesSignal,&QLineSeries::pointAdded,
                         this, &ChartView::dataOverfloated);
    }else{
        QObject::disconnect(seriesSignal,&QLineSeries::pointAdded,
                         this, &ChartView::dataOverfloated);
    }
}

void ChartView::dataOverfloated(int index){
    if(index==*signalLen){
        seriesSignal->clear();
    }
}

