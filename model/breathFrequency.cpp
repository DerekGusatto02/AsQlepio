#include "breathFrequency.h"
#include "healthyRange.h"

BreathFrequency::BreathFrequency(unsigned int id, std::string name, unsigned int reliability, Range range, unsigned int age, bool isUnderStress, SinDistribution* mesureDistribution)
    : Sensor(id, name, reliability, range, mesureDistribution), HealthyRange(id, name, reliability, range, Range(), mesureDistribution), StressMesurable(isUnderStress), age(age) {

    if(this->getIsUnderStress()){
        if(age<6){
            this->setHealthyRange(Range(60,80));
        }else if(age<12){
            this->setHealthyRange(Range(20,50));
        }else if(age<19){
            this->setHealthyRange(Range(15,30));
        }else{
            this->setHealthyRange(Range(20,30));
        }
    }else{
        if(age<1){
            this->setHealthyRange(Range(25,60));
        }else if(age<6){
            this->setHealthyRange(Range(20,30));
        }else if(age<12){
            this->setHealthyRange(Range(12,20));
        }else{
            this->setHealthyRange(Range(12,18));
        }
    }

}


BreathFrequency* BreathFrequency::clone() const{
    return new BreathFrequency(*this);
}

unsigned int BreathFrequency::getAge() const {
    return age;
}

void BreathFrequency::setAge(unsigned int age) {
    this->age = age;
}

QJsonObject BreathFrequency::toJson() const{
    QJsonObject json = HealthyRange::toJson();
    QJsonObject stress_json = StressMesurable::toJson();
    for(auto it = stress_json.begin(); it!=stress_json.end(); it++){
        json.insert(it.key(), it.value());
    }
    json["type"]="BreathFrequency";
    json["age"]=static_cast<int>(age);
    return json;
}

BreathFrequency* BreathFrequency::fromJson(QJsonObject json){
    unsigned int id = static_cast<unsigned int>(json["id"].toInt());
    std::string name = json["name"].toString().toStdString();
    unsigned int reliability = static_cast<unsigned int>(json["reliability"].toInt());
    Range range = Range::fromJson(json["range"].toObject());
    unsigned int age = static_cast<unsigned int>(json["age"].toInt());
    bool isUnderStress = json["isUnderStress"].toBool();
    return new BreathFrequency(id, name, reliability, range, age, isUnderStress, new SinDistribution());
}

void BreathFrequency::acceptSpecs(SensorSpecsVisitorInterface& v) {
    v.visitBreathFrequency(*this);
}

void BreathFrequency::acceptImage(SensorImageVisitorInterface& v) {
    v.visitBreathFrequency();
}
