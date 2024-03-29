#ifndef SIN_DISTRIBUTION_H
#define SIN_DISTRIBUTION_H

#include "mesureDistribution.h"
#include <vector>
#include "range.h"


class SinDistribution : public MesureDistribution {
public:
    SinDistribution(bool noise = false);
    ~SinDistribution();
    SinDistribution* clone() const override;
   std::vector<float> getDistribution(Range range) const override;
};

#endif // SIN_DISTRIBUTION_H
