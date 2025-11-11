#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include "sensor.h"

    class ChartWidget : public QChartView
{
    Q_OBJECT

public:
    explicit ChartWidget(QWidget *parent = nullptr);
    void updateData(const QVector<Sensor> &sensors);

private:
    QChart *m_chart;
    QLineSeries *m_tempSeries;
    QLineSeries *m_pressSeries;
    QLineSeries *m_humSeries;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    int m_timeStep = 0;
};

#endif // CHARTWIDGET_H
