#include "sinDistribution.h"
#include <cmath>
#include <random>

SinDistribution::SinDistribution(bool noise): MesureDistribution(noise){}
std::vector<float> SinDistribution::getDistribution(Range range) const {
    std::vector<float> distribution (20);
    float frequency = 10.0;
    float phase = 1.0;
    int numOfValues = 20;
    for(int i=0; i<numOfValues; i++){
        float normalized = 0.5 * (1 + std::sin(2.0 * M_PI * frequency * i / numOfValues + phase));
        distribution[i]=range.getMinimum() + normalized*(range.getMaximum()-range.getMinimum());
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

SinDistribution::~SinDistribution(){}
SinDistribution* SinDistribution::clone() const{
    return new SinDistribution(*this);
}
