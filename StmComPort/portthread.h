#ifndef PORTTHREAD_H
#define PORTTHREAD_H

#include <QThread>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QList>
#include <QStringList>

#include <QtDebug>
#include <QtCharts/QLineSeries>
#include "buttonsender.h"
#include "chartviewmedian.h"

class PortThread : public QThread
{ 
    Q_OBJECT
    private:
    QList<QSerialPortInfo> ports;
    QSerialPort curPort;
    double freq=1;// rad/s


private slots:
    void readFromPort();
    void handlePortError(QSerialPort::SerialPortError error);
public:
    QtCharts::QLineSeries *seriesSignal;
    ChartViewMedian *chartAfc;
    //*seriesAfc;

    PortThread();
    ~PortThread();
    signals:
    void sendPortsList(QStringList ports);
    void sendConnectionResult(bool res);
public slots:
    void refreshPorts();
    void connectToPort(int portNum);
    void disconnectToPort();
    void write2Port(QString data, QString ans, int id=0, QString arg="");
};

#endif // PORTTHREAD_H
