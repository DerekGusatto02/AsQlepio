#include "heartRate.h"

HeartRate::HeartRate(unsigned int id, std::string name, unsigned int reliability, Range range, bool isUnderStress, NormalDistribution* mesureDistribution)
    : Sensor(id, name, reliability, range, mesureDistribution), HealthyRange(id, name, reliability, range, Range(), mesureDistribution), StressMesurable(isUnderStress) {
    if(this->getIsUnderStress()){
        this->setHealthyRange(Range(130,170));
    }else{
         this->setHealthyRange(Range(60,100));
    }

}

HeartRate* HeartRate::clone() const{
    return new HeartRate(*this);

}


QJsonObject HeartRate::toJson() const{
    QJsonObject json = HealthyRange::toJson();
    QJsonObject stress_json = StressMesurable::toJson();
    for(auto it = stress_json.begin(); it!=stress_json.end(); it++){
        json.insert(it.key(), it.value());
    }
    json["type"]="HeartRate";
    return json;
}

HeartRate* HeartRate::fromJson(QJsonObject json){
    unsigned int id = static_cast<unsigned int>(json["id"].toInt());
    std::string name = json["name"].toString().toStdString();
    unsigned int reliability = static_cast<unsigned int>(json["reliability"].toInt());
    Range range = Range::fromJson(json["range"].toObject());
    bool isUnderStress = json["isUnderStress"].toBool();
    return new HeartRate(id, name, reliability, range, isUnderStress, new NormalDistribution());
}

void HeartRate::acceptSpecs(SensorSpecsVisitorInterface& v) {
    v.visitHeartRate(*this);
}

void HeartRate::acceptImage(SensorImageVisitorInterface& v) {

    v.visitHeartRate();
}

