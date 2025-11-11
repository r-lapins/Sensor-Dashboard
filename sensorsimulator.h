#ifndef SENSORSIMULATOR_H
#define SENSORSIMULATOR_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include "sensor.h"

class SensorSimulator : public QObject
{
    Q_OBJECT

public:
    explicit SensorSimulator(QObject *parent = nullptr);

    // rozpoczęcie i zatrzymanie symulacji
    void start(int intervalMs = 1000);
    void stop();

signals:
    // sygnał emitowany, gdy dostępne są nowe dane
    void dataUpdated(const QVector<Sensor> &sensors);

private slots:
    void generateData();

private:
    QTimer m_timer;
    QVector<Sensor> m_sensors;
};

#endif // SENSORSIMULATOR_H
