#ifndef SENSOR_LOADER_H
#define SENSOR_LOADER_H

#include <QVector>
#include "sensor.h"

class SensorLoader {
public:
    std::vector<Sensor*> loadFromFile(const QString& filename);
};

#endif // SENSOR_LOADER_H
