#include "buttonchartseries2file.h"

void ButtonChartSeries2File::onClick(){
    setEnabled(false);
    auto points=static_cast<ChartView *>(parent())->seriesSignal->pointsVector();
    /*QString text2Save="";
    foreach (auto point, points) {
        text2Save+=QString::number(point.x()) % " " % QString::number(point.y()) % "\n";
    }
    */
    QString textFilePath = QFileDialog::getSaveFileName(this, tr("Сохранить точки графика"),
                                                        QTime::currentTime().toString("h_m") % ".txt",
                                                        tr("Текстовые документы (*.txt)"));

    QFile textFile(textFilePath);
    if(!textFile.open(QFile::WriteOnly | QFile::Text)){
        setEnabled(true);
        return;
        //qDebug()<<"can not open to write";
    }

    QTextStream textStream(&textFile);
    foreach (auto point, points) {
        textStream <<QString::number(point.x())<<" "<<QString::number(point.y())<<"\n";
    }
    textFile.flush();
    textFile.close();
    setEnabled(true);
}
