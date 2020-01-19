#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chartViewSignal=ui->chartView;
    chartViewAfc=ui->chartViewAfc;
    chartViewAfc->setClearOnOverfloat(false);
    //chartViewAfc->seriesSignal->setPen(QPen(Qt::NoPen));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::appendWidget(QWidget *w, bool spaceAfter){
    ui->verticalLayoutTab_1->addWidget(w);
    if(spaceAfter){
        ui->verticalLayoutTab_1->addSpacing(4);
    }
}

void MainWindow::on_btnRefreshPorts_clicked()
{
    callRefreshPortsList();
}

void MainWindow::receivePortsList(QStringList ports){
    ui->comboBoxPortsList->clear();
    ui->comboBoxPortsList->addItems(ports);

    ui->btnConnect->setEnabled(true);
}

void MainWindow::on_btnConnect_clicked()
{
    ui->btnConnect->setEnabled(false);
    if(ui->comboBoxPortsList->count()==0){
        return;
    }
    callConnection(ui->comboBoxPortsList->currentIndex());
}

void MainWindow::receiveConnectionResult(bool res){
    ui->btnConnect->setEnabled(true);
    if(res){
        qDebug()<<"connected";
        ui->labelConnectState->setText(
                    "connected to "+ui->comboBoxPortsList->currentText());
        ui->labelConnectState->setStyleSheet("QLabel { color: green }");
    }
    else {
        qDebug()<<"disconnected";
        ui->labelConnectState->setText("disconnected");
        ui->labelConnectState->setStyleSheet("QLabel { color: red }");
}
}

void MainWindow::on_btnDisconnect_clicked()
{
    callDisconnect();
}
