#include "healthyRange.h"

HealthyRange::HealthyRange(unsigned int id, std::string name, unsigned int reliability, Range range, Range healthyRange, MesureDistribution* mesureDistribution)
    : Sensor(id, name, reliability, range, mesureDistribution),
    healthyRange(healthyRange) {}


HealthyRange* HealthyRange::clone() const{
    return new HealthyRange(*this);
}


Range HealthyRange::getHealthyRange() const {
    return this->healthyRange;
}

void HealthyRange::setHealthyRange(Range range) {
    this->healthyRange = range;
}

bool HealthyRange::isHealthy(float value) const{
    return this->healthyRange.contains(value);
}

QJsonObject HealthyRange::toJson() const{
    QJsonObject json;
    json = Sensor::toJson();
    json["healtyrange"] = healthyRange.toJson();
    return json;
}

HealthyRange* HealthyRange::fromJson(QJsonObject json){
    unsigned int id = static_cast<unsigned int>(json["id"].toInt());
    std::string name = json["name"].toString().toStdString();
    unsigned int reliability = static_cast<unsigned int>(json["reliability"].toInt());
    Range range = Range::fromJson(json["range"].toObject());
    Range healthyRange = Range::fromJson(json["healthyRange"].toObject());
    return new HealthyRange(id, name, reliability, range, healthyRange);
}
