#include "portthread.h"

PortThread::PortThread()
{
    QObject::connect(&curPort,SIGNAL(readyRead()),
                     this,SLOT(readFromPort()));
    QObject::connect(&curPort,SIGNAL(errorOccurred(QSerialPort::SerialPortError)),
                     this,SLOT(handlePortError(QSerialPort::SerialPortError)));
}

PortThread::~PortThread(){
    curPort.close();
}

void PortThread::refreshPorts(){
    ports=QSerialPortInfo::availablePorts();
    QStringList portsList={};
    for(auto port:ports){
        portsList.append(port.portName());
    }
    sendPortsList(portsList);
}

void PortThread::connectToPort(int portNum){
    disconnectToPort();
    curPort.setPort(ports.at(portNum));
    bool conRes=curPort.open(QIODevice::ReadWrite);
    qDebug()<<conRes;
    sendConnectionResult(conRes);
}

void PortThread::disconnectToPort(){
    curPort.clear();
    curPort.close();
    sendConnectionResult(false);
}

void PortThread::write2Port(QString data, QString ans, int id, QString arg){
    curPort.waitForBytesWritten();
    QByteArray parcel={};
    parcel.append(data);
    qDebug()<<"Writing "<<parcel;
    curPort.write(parcel);

    if(id==1){//it's a frequency
        freq=arg.replace(",",".").toDouble();
    }
}

void PortThread::readFromPort(){
    QByteArray parcel={};
    bool *isDouble=new bool(0);
    double data;
    while(curPort.bytesAvailable()){
        parcel.append(curPort.readLine());
        //qDebug()<<parcel;
        /*
        if((parcel.startsWith('+')||parcel.startsWith('-'))&&parcel.endsWith('\n')){

        }*/

        if(parcel.at(0)=='d'){//afc delay
            data=parcel.mid(1,parcel.length()-2).toDouble(isDouble);
            if(isDouble){
                //seriesAfc->append(seriesAfc->points().length(),data);
                chartAfc->addDelayAtFreq(data, freq);
                return;
            }
        }
        if(parcel.at(0)=='a'){//afc amp
            data=parcel.mid(1,parcel.length()-2).toDouble(isDouble);
            if(isDouble){
                //seriesAfc->append(seriesAfc->points().length(),data);
                chartAfc->addAmpAtFreq(data, freq);
                return;
            }
        }
        //data=parcel.mid(1,4).toDouble(isDouble);
        data=parcel.mid(0,5).toDouble(isDouble);
        //parcel=parcel.mid(1,4);
        if(isDouble){
            //data*=parcel.at(0)=='+'?1:-1;
            seriesSignal->append(seriesSignal->count(), data);
        }

        parcel.clear();
    }
}

void PortThread::handlePortError(QSerialPort::SerialPortError error){
    qDebug()<<error;
    //curPort.clearError();
}
