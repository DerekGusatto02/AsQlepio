#include "sensor.h"

Sensor::Sensor(unsigned int id, std::string name, unsigned int reliability, Range range, MesureDistribution* mesureDistribution):
    id(id),
    name(name),
    reliability(reliability),
    range(range){
    if (mesureDistribution)
        this->mesureDistribution = mesureDistribution->clone();
    else
        this->mesureDistribution = nullptr;
}
Sensor::Sensor(const Sensor& other)
    : id(other.id), name(other.name), reliability(other.reliability), range(other.range) {

    if (other.mesureDistribution)
        mesureDistribution = other.mesureDistribution->clone();
    else
        mesureDistribution = nullptr;

}

Sensor::~Sensor() {
    delete mesureDistribution;
}

Sensor& Sensor::operator=(const Sensor& other){
    if (this != &other)
    {
        id = other.id;
        name = other.name;
        reliability = other.reliability;
        range = other.range;


        delete mesureDistribution;

        if (other.mesureDistribution)
            mesureDistribution = other.mesureDistribution->clone();
        else
            mesureDistribution = nullptr;
    }


    return *this;
}




unsigned int Sensor::getId() const {
    return id;
}

std::string Sensor::getName() const {
    return name;
}

unsigned int Sensor::getReliability() const {
    return reliability;
}

Range Sensor::getRange() const {
    return range;
}

MesureDistribution* Sensor::getMesureDistribution() const {
    return mesureDistribution;
}
void Sensor::setId(unsigned int i) {
    id = i;
}

void Sensor::setName(std::string n) {
    name = n;
}

void Sensor::setReliability(unsigned int rel) {
    reliability = rel;
}


void Sensor::setRange(Range r) {
    range = r;
}

QJsonObject Sensor::toJson() const {
    QJsonObject json;
    json["id"] = static_cast<int>(id);
    json["name"] = QString::fromStdString(name);
    json["reliability"] = static_cast<int>(reliability);
    json["range"] = range.toJson();
    return json;
}

