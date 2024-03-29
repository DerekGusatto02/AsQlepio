#ifndef SENSOR_SAVER_H
#define SENSOR_SAVER_H

#include <QVector>
#include "sensor.h"

class SensorSaver {
public:
    SensorSaver(const QVector<Sensor*>& s);
    void saveToFile(const QString& filename = "nuovo");

private:
    QVector<Sensor*> sensors;
};

#endif // SENSOR_SAVER_H
