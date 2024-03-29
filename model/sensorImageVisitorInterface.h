#ifndef SENSORIMAGEVISITORINTERFACE_H
#define SENSORIMAGEVISITORINTERFACE_H

class Temperature;
class HeartRate;
class BreathFrequency;
class OxygenSaturation;
class BloodPressure;

class SensorImageVisitorInterface {
public:
    virtual void visitTemperature() = 0;
    virtual void visitHeartRate() = 0;
    virtual void visitBreathFrequency() = 0;
    virtual void visitOxygenSaturation() = 0;
    virtual void visitBloodPressure() = 0;
};

#endif // SENSORIMAGEVISITORINTERFACE_H
