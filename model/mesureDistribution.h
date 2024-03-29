#ifndef MESURE_DISTRIBUTION_H
#define MESURE_DISTRIBUTION_H

#include <vector>
#include "range.h"

class MesureDistribution {
protected:
    bool noise;

public:
    MesureDistribution(bool noise = false);
    MesureDistribution(const MesureDistribution& other);
    virtual ~MesureDistribution() = 0;
    virtual MesureDistribution* clone() const = 0;
    bool getNoise() const;
    void setNoise(bool noise);
    virtual std::vector<float> getDistribution(Range range) const = 0;
};

#endif // MESURE_DISTRIBUTION_H
