#ifndef RANGE_H
#define RANGE_H

#include <QJsonObject>

class Range {
public:
    unsigned int minimum;
    unsigned int maximum;
public:
    Range(unsigned int minimum = 0, unsigned int maximum = 0);
    unsigned int getMaximum() const;
    unsigned int getMinimum() const;
    void setMaximum(unsigned int maximum);
    void setMinimum(unsigned int minimum);
    bool contains(float value) const;
    QJsonObject toJson() const;
    static Range fromJson(QJsonObject json);
};

#endif // RANGE_H
