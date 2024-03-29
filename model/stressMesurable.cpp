#include "stressMesurable.h"

StressMesurable::StressMesurable(bool isUnderStress) 
    : isUnderStress(isUnderStress) {}

StressMesurable::~StressMesurable() {}

StressMesurable* StressMesurable::clone() const {
    return new StressMesurable(*this);
}

bool StressMesurable::getIsUnderStress() const {
    return this->isUnderStress;
}

void StressMesurable::setIsUnderStress(bool isUnderStress) {
    this->isUnderStress = isUnderStress;
}

QJsonObject StressMesurable::toJson() const{
    QJsonObject json;
    json["isUnderStress"] = isUnderStress;
    return json;
}
