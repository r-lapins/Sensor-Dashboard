#include "sensorsimulator.h"
#include <QDateTime>
#include <QDebug>
#include <random>

SensorSimulator::SensorSimulator(QObject *parent)
    : QObject(parent)
{
    // przykładowe czujniki
    m_sensors = {
        {"Temperature", "°C", 0.0, QDateTime::currentDateTime()},
        {"Pressure", "hPa", 0.0, QDateTime::currentDateTime()},
        {"Humidity", "%", 0.0, QDateTime::currentDateTime()}
    };

    connect(&m_timer, &QTimer::timeout, this, &SensorSimulator::generateData);
}

void SensorSimulator::start(int intervalMs)
{
    if (!m_timer.isActive()) {
        m_timer.start(intervalMs);
        qDebug() << "Sensor simulation started.";
    }
}

void SensorSimulator::stop()
{
    if (m_timer.isActive()) {
        m_timer.stop();
        qDebug() << "Sensor simulation stopped.";
    }
}

void SensorSimulator::generateData()
{
    static std::random_device rd;
    static std::mt19937 rng(rd());

    // rozkłady dla każdego typu czujnika
    std::uniform_real_distribution<double> tempDist(17.0, 23.0);   // °C
    std::uniform_real_distribution<double> pressDist(1003.0, 1023.0); // hPa
    std::uniform_real_distribution<double> humDist(45.0, 55.0);    // %

    for (auto &s : m_sensors) {
        if (s.name == "Temperature")
            s.value = tempDist(rng);
        else if (s.name == "Pressure")
            s.value = pressDist(rng);
        else if (s.name == "Humidity")
            s.value = humDist(rng);

        s.timestamp = QDateTime::currentDateTime();
    }

    emit dataUpdated(m_sensors);
}
