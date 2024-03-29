#include "bloodPressure.h"
#include "healthyRange.h"

BloodPressure::BloodPressure(unsigned int id, std::string name, unsigned int reliability, Range range, UniformDistribution* mesuredistribution): Sensor(id, name, reliability, range, mesuredistribution), sistolicHealthyRange(Range(90,120)), diastolicHealthyRange(Range(60,80)){}

BloodPressure* BloodPressure::clone() const{
    return new BloodPressure(*this);
}

Range BloodPressure::getSistolicHealthyRange(){
    return sistolicHealthyRange;
}

Range BloodPressure::getDiastolicHealthyRange(){
    return diastolicHealthyRange;
}

void BloodPressure::setSistolicHealthyRange(Range range){
    sistolicHealthyRange = range;
}

void BloodPressure::setDiastolicHealthyRange(Range range){
    diastolicHealthyRange = range;
}

bool BloodPressure::isHealthy(float value) const {
    return this->sistolicHealthyRange.contains(value);
}

bool BloodPressure::isHealthyDiastolic(float value) const {
    return this->diastolicHealthyRange.contains(value);
}


QJsonObject BloodPressure::toJson() const{
    QJsonObject json = Sensor::toJson();
    json["type"] = "BloodPressure";
    return json;
}

BloodPressure* BloodPressure::fromJson(QJsonObject json){
    unsigned int id = static_cast<unsigned int>(json["id"].toInt());
    std::string name = json["name"].toString().toStdString();
    unsigned int reliability = static_cast<unsigned int>(json["reliability"].toInt());
    Range range = Range::fromJson(json["range"].toObject());
    return new BloodPressure(id, name, reliability, range, new UniformDistribution());
}

void BloodPressure::acceptImage(SensorImageVisitorInterface& v) {
    v.visitBloodPressure();
}

void BloodPressure::acceptSpecs(SensorSpecsVisitorInterface& v) {
    v.visitBloodPressure();
}