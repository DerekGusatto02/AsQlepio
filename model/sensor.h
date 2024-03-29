#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <QJsonObject>
#include <QJsonDocument>
#include "range.h"
#include "mesureDistribution.h"
#include "sensorSpecsVisitorInterface.h"
#include "sensorImageVisitorInterface.h"

class Sensor{
    private:
        unsigned int id;
        std::string name;
        unsigned int reliability;
        Range range;
        MesureDistribution* mesureDistribution;
    public:
        Sensor(unsigned int id = 0, std::string name = "", unsigned int reliability = 0, Range range = Range(), MesureDistribution* mesureDistribution = nullptr);
        Sensor(const Sensor& other);
        virtual ~Sensor();
        Sensor& operator=(const Sensor& other);
        virtual Sensor* clone() const = 0;
        unsigned int getId() const;
        std::string getName() const;
        unsigned int getReliability() const;
        Range getRange() const;
        MesureDistribution* getMesureDistribution() const;
        void setId(unsigned int id);
        void setName(std::string name);
        void setReliability(unsigned int reliability);
        void setRange(Range range);
        virtual bool isHealthy(float value) const =0;
        virtual void acceptSpecs(SensorSpecsVisitorInterface&) = 0;
        virtual void acceptImage(SensorImageVisitorInterface&) = 0;
        virtual QJsonObject toJson() const;
};

#endif // SENSOR_H
