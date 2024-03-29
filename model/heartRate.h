#ifndef HEART_RATE_H
#define HEART_RATE_H

#include "healthyRange.h"
#include "stressMesurable.h"
#include "normalDistribution.h"

class HeartRate : public HealthyRange, public StressMesurable {

    public:
    HeartRate(unsigned int id = 0, std::string name = "", unsigned int reliability = 0, Range range = Range(), bool isUnderStress = false, NormalDistribution* mesureDistribution = nullptr);
    virtual HeartRate* clone() const override;
    QJsonObject toJson() const override;

    static HeartRate* fromJson(QJsonObject json);
    void acceptSpecs(SensorSpecsVisitorInterface&);
    void acceptImage(SensorImageVisitorInterface&);
};

#endif // HEART_RATE_H
