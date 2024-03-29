#ifndef BREATH_FREQUENCY_H
#define BREATH_FREQUENCY_H

#include "healthyRange.h"
#include "stressMesurable.h"
#include "sinDistribution.h"

class BreathFrequency : public HealthyRange, public StressMesurable {
private:
    unsigned int age;
    public:
    BreathFrequency(unsigned int id = 0, std::string name = "", unsigned int reliability = 0, Range range = Range(), unsigned int age = 1, bool isUnderStress = false, SinDistribution* mesureDistribution = nullptr);
    virtual BreathFrequency* clone() const override;
    unsigned int getAge() const;
    void setAge(unsigned int age);
    QJsonObject toJson() const override;
    static BreathFrequency* fromJson(QJsonObject json);
    void acceptSpecs(SensorSpecsVisitorInterface&);
    void acceptImage(SensorImageVisitorInterface&);
};
#endif // BREATH_FREQUENCY_H
