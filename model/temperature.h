#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "healthyRange.h"
#include "normalDistribution.h"

class Temperature : public HealthyRange {
    private:
    bool unitOfMesure; // true = Celsius, false = Fahrenheit
    public:
    Temperature(unsigned int id = 0, std::string name = "", unsigned int reliability = 0, Range range = Range(), bool unitOfMesure = false, NormalDistribution* mesureDistribution = nullptr);
    virtual Temperature* clone() const override;
    bool getUnitOfMesure() const;
    void setUnitOfMesure(bool unitOfMesure);
    bool convert(bool unitOfMesure);
    QJsonObject toJson() const override;
    static Temperature* fromJson(QJsonObject json);
    void acceptSpecs(SensorSpecsVisitorInterface&);
    void acceptImage(SensorImageVisitorInterface&);
};
#endif // TEMPERATURE_H
