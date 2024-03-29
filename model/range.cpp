#include <iostream>
#include "range.h"

Range::Range(unsigned int minimum, unsigned int maximum): minimum(minimum), maximum(maximum) {};

unsigned int Range::getMaximum() const{
    return maximum;
};

unsigned int Range::getMinimum() const{
    return minimum;
};

void Range::setMaximum(unsigned int maximum){
    this->maximum = maximum;
};

void Range::setMinimum(unsigned int minimum){
    this->minimum = minimum;
};

bool Range::contains(float value) const{
    return (value >= this->getMinimum() && value <= this->getMaximum());
};

 QJsonObject Range::toJson() const{
    QJsonObject json;
    json["minimum"] = static_cast<int>(minimum);
    json["maximum"] = static_cast<int>(maximum);
    return json;
 }

    Range Range::fromJson(QJsonObject json){
        unsigned int minimum = static_cast<unsigned int>(json["minimum"].toInt());
        unsigned int maximum = static_cast<unsigned int>(json["maximum"].toInt());
        return Range(minimum, maximum);
    }


