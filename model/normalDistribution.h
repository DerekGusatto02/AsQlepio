#ifndef NORMAL_DISTRIBUTION_H
#define NORMAL_DISTRIBUTION_H

#include "mesureDistribution.h"
#include <vector>
#include "range.h"


class NormalDistribution : public MesureDistribution {
public:
   NormalDistribution(bool noise=false);
   ~NormalDistribution();
   NormalDistribution* clone() const override;
   std::vector<float> getDistribution(Range range) const override;
};

#endif // NORMAL_DISTRIBUTION_H
