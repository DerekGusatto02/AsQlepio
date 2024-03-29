#ifndef UNIFORM_DISTRIBUTION_H
#define UNIFORM_DISTRIBUTION_H

#include "mesureDistribution.h"
#include <vector>
#include "range.h"

class UniformDistribution : public MesureDistribution {
public:
   UniformDistribution(bool noise = false);
   ~UniformDistribution();
   UniformDistribution* clone() const override;
   std::vector<float> getDistribution(Range range) const override;
};

#endif // UNIFORM_DISTRIBUTION_H
