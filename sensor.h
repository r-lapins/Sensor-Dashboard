#ifndef SENSOR_H
#define SENSOR_H

#include <QString>
#include <QDateTime>

struct Sensor
{
    QString name;        // np. "Temperature"
    QString unit;        // np. "°C"
    double value = 0.0;
    QDateTime timestamp; // czas ostatniego pomiaru
};

#endif // SENSOR_H
