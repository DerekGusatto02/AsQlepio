#ifndef STRESSMESURABLE_H
#define STRESSMESURABLE_H

#include <QJsonObject>
#include <QJsonDocument>

class StressMesurable {
private:
    bool isUnderStress;
public:
    StressMesurable(bool isUnderStress = false);
    ~StressMesurable();
    virtual StressMesurable* clone() const;
    bool getIsUnderStress() const;
    void setIsUnderStress(bool isUnderStress);
    QJsonObject toJson() const;
};

#endif // STRESSMESURABLE_H
