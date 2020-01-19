#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QChart>
#include <QLineSeries>
#include <QStringList>
#include <QWheelEvent>
#include "chartview.h"
#include "chartviewmedian.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ChartView *chartViewSignal;
    ChartViewMedian *chartViewAfc;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


public:
    void appendWidget(QWidget *w, bool spaceAfter=false);
public slots:
    void receivePortsList(QStringList ports);
    void receiveConnectionResult(bool res);
    signals:
    void callRefreshPortsList();
    void callConnection(int portNum);
    void callDisconnect();
private slots:
    void on_btnRefreshPorts_clicked();
    void on_btnConnect_clicked();
    void on_btnDisconnect_clicked();
};

#endif // MAINWINDOW_H
