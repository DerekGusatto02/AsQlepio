#include "uniformDistribution.h"
#include <QRandomGenerator>
#include <random>

UniformDistribution::UniformDistribution(bool noise): MesureDistribution(noise){}

std::vector<float> UniformDistribution::getDistribution(Range range) const {
    std::vector<float> distribution(20);
    for(int i=0; i<20; i++){
        distribution[i]=QRandomGenerator::global()->generateDouble()*(range.getMaximum()-range.getMinimum())+range.getMinimum();
        if(this->noise){
            std::random_device rd;
            std::mt19937 gen(rd());
            std::normal_distribution<> d(0,1);
            double n = d(gen);
            distribution[i]+= n;
        }
    }
    return distribution;
}

UniformDistribution::~UniformDistribution(){}

UniformDistribution* UniformDistribution::clone() const {
    return new UniformDistribution(*this);
}
