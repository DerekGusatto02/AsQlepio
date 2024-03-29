#ifndef OXYGEN_SATURATION_H
#define OXYGEN_SATURATION_H

#include "healthyRange.h"
#include "uniformDistribution.h"

class OxygenSaturation : public HealthyRange {
    public:
    OxygenSaturation(unsigned int id = 0, std::string name = "", unsigned int reliability = 0, Range range = Range(), UniformDistribution* mesureDistribution = nullptr);
    virtual OxygenSaturation* clone() const override;
    QJsonObject toJson() const override;
    static OxygenSaturation* fromJson(QJsonObject json);
    void acceptImage(SensorImageVisitorInterface&);
    void acceptSpecs(SensorSpecsVisitorInterface&);
};
#endif // OXYGEN_SATURATION_H


