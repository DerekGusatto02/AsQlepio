#include "temperature.h"
#include "sensor.h"

Temperature::Temperature(unsigned int id, std::string name, unsigned int reliability, Range range, bool unitOfMesure, NormalDistribution* mesureDistribution)
    : Sensor(id, name, reliability, range, mesureDistribution), HealthyRange(id, name, reliability, range, Range(), mesureDistribution), unitOfMesure(unitOfMesure) {
    if(this->getUnitOfMesure()){
        this->setHealthyRange(Range(36,37));
    }else{
        this->setHealthyRange(Range(97,99));
    }
}

 bool Temperature::getUnitOfMesure() const {
     return unitOfMesure;
 }

 void Temperature::setUnitOfMesure(bool unitOfMesure) {
     this->unitOfMesure = unitOfMesure;
 }

 bool Temperature::convert(bool unitOfMesure){
     if(this->unitOfMesure && !unitOfMesure){
        //f = (c*9.0/5.0)+32
         this->unitOfMesure = false;
         return false;

     }else if(!this->unitOfMesure && unitOfMesure){
        // c= (f-32)*5.0/9.0
         this->unitOfMesure = true;
         return true;

     }
    return unitOfMesure;
 }

 Temperature* Temperature::clone() const {
     return new Temperature(*this);
 }

 QJsonObject Temperature::toJson() const{
     QJsonObject json = HealthyRange::toJson();
     json["unitOfMesure"] = unitOfMesure;
     json["type"] = "Temperature";

     return json;
 }

Temperature* Temperature::fromJson(QJsonObject json){
    unsigned int id = static_cast<unsigned int>(json["id"].toInt());
    std::string name = json["name"].toString().toStdString();
    unsigned int reliability = static_cast<unsigned int>(json["reliability"].toInt());
    Range range = Range::fromJson(json["range"].toObject());
    bool unitOfMesure = json["unitOfMesure"].toBool();
    return new Temperature(id, name, reliability, range, unitOfMesure, new NormalDistribution() );
}

void Temperature::acceptSpecs(SensorSpecsVisitorInterface& v) {
    v.visitTemperature(*this);
}

void Temperature::acceptImage(SensorImageVisitorInterface& v) {
    v.visitTemperature();
}
