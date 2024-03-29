#include "normalDistribution.h"
#include <random>
NormalDistribution::NormalDistribution(bool noise) : MesureDistribution(noise){}
std::vector<float> NormalDistribution::getDistribution(Range range) const {
    std::vector<float> distribution(20);
    std::default_random_engine generator;
    std::normal_distribution<float> d(((range.getMaximum()+range.getMinimum())/2), 1.0);
    for(int i=0; i<20; i++){
        distribution[i]=d(generator);
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

NormalDistribution::~NormalDistribution(){}
NormalDistribution* NormalDistribution::clone() const {
    return new NormalDistribution(*this);
}
