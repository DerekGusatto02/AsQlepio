#ifndef BLOODPRESSURE_H
#define BLOODPRESSURE_H
#include "sensor.h"
#include "uniformDistribution.h"
#include <QJsonObject>
#include <QJsonDocument>

class BloodPressure: public Sensor{
    private:
    Range sistolicHealthyRange;
    Range diastolicHealthyRange;

    public:
    BloodPressure(unsigned int id = 0, std::string name = "", unsigned int reliability = 0, Range range = Range(), UniformDistribution* mesuredistribution = nullptr);
    virtual BloodPressure* clone() const override;
    Range getSistolicHealthyRange();
    Range getDiastolicHealthyRange();
    void setSistolicHealthyRange(Range range);
    void setDiastolicHealthyRange(Range range);
    bool isHealthy(float value) const override;
    bool isHealthyDiastolic(float value) const;
    QJsonObject toJson() const override;
    static BloodPressure* fromJson(QJsonObject json);
    void acceptSpecs(SensorSpecsVisitorInterface&);
    void acceptImage(SensorImageVisitorInterface&);
};

#endif // BLOODPRESSURE_H
