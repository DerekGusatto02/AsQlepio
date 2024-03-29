#include <vector>
#include "mesureDistribution.h"


MesureDistribution::MesureDistribution(bool noise) : noise(noise) {}

MesureDistribution::MesureDistribution(const MesureDistribution& other) : noise(other.noise) {}

MesureDistribution::~MesureDistribution() {}

bool MesureDistribution::getNoise() const { return noise; }

void MesureDistribution::setNoise(bool noise) { this->noise = noise; }

