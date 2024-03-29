#include "oxygenSaturation.h"

OxygenSaturation::OxygenSaturation(unsigned int id, std::string name, unsigned int reliability, Range range, UniformDistribution* mesureDistribution)
    : Sensor(id, name, reliability, range, mesureDistribution), HealthyRange(id, name, reliability, range, Range(95,100), mesureDistribution) {}

OxygenSaturation* OxygenSaturation::clone() const {
    return new OxygenSaturation(*this);

}

QJsonObject OxygenSaturation::toJson() const{
    QJsonObject json = HealthyRange::toJson();
    json["type"] = "OxygenSaturation";

    return json;
}

OxygenSaturation* OxygenSaturation::fromJson(QJsonObject json){
    unsigned int id = static_cast<unsigned int>(json["id"].toInt());
    std::string name = json["name"].toString().toStdString();
    unsigned int reliability = static_cast<unsigned int>(json["reliability"].toInt());
    Range range = Range::fromJson(json["range"].toObject());
    return new OxygenSaturation(id, name, reliability, range, new UniformDistribution());
}

void OxygenSaturation::acceptImage(SensorImageVisitorInterface& v) {

    v.visitOxygenSaturation();
}

void OxygenSaturation::acceptSpecs(SensorSpecsVisitorInterface& v) {

    v.visitOxygenSaturation();
}
