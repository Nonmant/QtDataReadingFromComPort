#include "mainwindow.h"
#include "portthread.h"
#include "buttonsender.h"
#include <QApplication>
#include <QStringList>

int readParams(MainWindow *w,QString paramsPath=":/params.json");
void addDFButtons(MainWindow *w);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    readParams(&w);
    addDFButtons(&w);

    auto thread=new PortThread();

    QObject::connect(&w,SIGNAL(callRefreshPortsList()),
                     thread,SLOT(refreshPorts()));

    QObject::connect(thread,SIGNAL(sendPortsList(QStringList)),
                     &w,SLOT(receivePortsList(QStringList)));

    QObject::connect(&w,SIGNAL(callConnection(int)),
                     thread,SLOT(connectToPort(int)));

    QObject::connect(thread, SIGNAL(sendConnectionResult(bool)),
                     &w,SLOT(receiveConnectionResult(bool)));

    QObject::connect(&w, SIGNAL(callDisconnect()),
                     thread,SLOT(disconnectToPort()));

    for( auto child:w.findChildren<ButtonSender *>(QString(), Qt::FindDirectChildrenOnly)){
        QObject::connect(child,&ButtonSender::write2Thread,
                         thread,&PortThread::write2Port);
    }

    thread->seriesSignal=w.chartViewSignal->seriesSignal;
    thread->chartAfc=w.chartViewAfc;

    return a.exec();

    //QObject::connect()
}

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include "buttonsender.h"

#include "portthread.h"

#include <QtDebug>
int readParams(MainWindow *w, QString paramsPath){
    //if(!paramsPath.size())paramsPath=":/params.json";

    QFile file(paramsPath);
    file.open(QIODevice::ReadOnly);
    //auto s=QString::fromUtf8(file.readAll());
    QString s=QString::fromUtf8(file.readAll());

    QByteArray array;
        // Перегоняем строку в массив байтов
        array.append(s);

    QJsonDocument json=QJsonDocument::fromJson(array);

    QJsonObject obj=json.object();
    auto btnsAr=obj.take("buttons").toArray();
    for(auto val:btnsAr){
        auto btnObj=val.toObject();

        QString inputType="";

        QStringList names={},values={};

        if(btnObj["argument"].isString()){
            inputType=btnObj["argument"].toString();
        }
        if(btnObj["argument"].isObject()){
            auto btPoles=btnObj["argument"].toObject()["poles"].toArray();
            auto btValues=btnObj["argument"].toObject()["values"].toArray();
            for(int i=0;i<btPoles.count();++i){
                names.append(btPoles[i].toString());
                values.append(btValues[i].toString());
            }
        }

        auto btnSender=new ButtonSender(btnObj["name"].toString(),
                btnObj["str2send"].toString(),
                btnObj["str2get"].toString(),
                btnObj["description"].toString(),
                inputType,
                names,
                values);
        if(btnObj["id"].isDouble()){
            btnSender->id=int(btnObj["id"].toDouble());
        }
        if(btnSender->input!=nullptr){
            w->appendWidget(btnSender->input);
        }
        w->appendWidget(btnSender->button, true);
        btnSender->setParent(w);

        //btnSender->button->click();
    }
    return 0;
}


#include "buttonsenderpoly.h"
void addDFButtons(MainWindow *w){

    auto btnDFA = new ButtonSenderPoly("A дискр. фильтра", "dfa%1", "",
                                       "Коэффициенты числителя дискр. пер. функции фильтра");
    w->appendWidget(btnDFA->input);
    w->appendWidget(btnDFA->button,true);
    btnDFA->setParent(w);

    auto btnDFB = new ButtonSenderPoly("B дискр. фильтра", "dfb%1", "",
                                       "Коэффициенты знаменателя дискр. пер. функции фильтра");
    w->appendWidget(btnDFB->input);
    w->appendWidget(btnDFB->button,true);
    btnDFB->setParent(w);
}
