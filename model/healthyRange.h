#ifndef HEALTHYRANGE_H
#define HEALTHYRANGE_H

#include "sensor.h"
#include <QJsonObject>
#include <QJsonDocument>

class HealthyRange : virtual public Sensor {
private:
    Range healthyRange;

public:
    HealthyRange(unsigned int id = 0, std::string name = "", unsigned int reliability = 0, Range range = Range(), Range healthyRange = Range(), MesureDistribution* mesureDistribution = nullptr);
    virtual HealthyRange* clone() const override;
    Range getHealthyRange() const;

    void setHealthyRange(Range range);

    bool isHealthy(float value) const override;

    QJsonObject toJson() const override;

    static HealthyRange* fromJson(QJsonObject json);


    void acceptSpecs(SensorSpecsVisitorInterface&) {};
    void acceptImage(SensorImageVisitorInterface&) {};
};

#endif // HEALTHYRANGE_H
