#include "chartwidget.h"
#include <QDateTime>

ChartWidget::ChartWidget(QWidget *parent)
    : QChartView(parent)
{
    m_chart = new QChart();
    m_tempSeries = new QLineSeries();
    m_pressSeries = new QLineSeries();
    m_humSeries = new QLineSeries();

    m_tempSeries->setName("Temperature (°C)");
    m_pressSeries->setName("Pressure (hPa)");
    m_humSeries->setName("Humidity (%)");

    m_chart->addSeries(m_tempSeries);
    m_chart->addSeries(m_pressSeries);
    m_chart->addSeries(m_humSeries);

    m_axisX = new QValueAxis;
    m_axisX->setTitleText("Time [s]");
    m_axisX->setRange(0, 30);

    m_axisY = new QValueAxis;
    m_axisY->setTitleText("Value");
    m_axisY->setRange(0, 1100);

    m_chart->addAxis(m_axisX, Qt::AlignBottom);
    m_chart->addAxis(m_axisY, Qt::AlignLeft);

    for (auto series : {m_tempSeries, m_pressSeries, m_humSeries}) {
        series->attachAxis(m_axisX);
        series->attachAxis(m_axisY);
    }

    setChart(m_chart);
    setRenderHint(QPainter::Antialiasing);
}

void ChartWidget::updateData(const QVector<Sensor> &sensors)
{
    ++m_timeStep;

    for (const auto &s : sensors) {
        if (s.name == "Temperature")
            m_tempSeries->append(m_timeStep, s.value);
        else if (s.name == "Pressure")
            m_pressSeries->append(m_timeStep, s.value);
        else if (s.name == "Humidity")
            m_humSeries->append(m_timeStep, s.value);
    }

    if (m_timeStep > 30)
        m_axisX->setRange(m_timeStep - 30, m_timeStep);
}
