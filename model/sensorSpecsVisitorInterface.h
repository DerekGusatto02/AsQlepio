#ifndef SENSORSPECSVISITORINTERFACE_H
#define SENSORSPECSVISITORINTERFACE_H

class Temperature;
class HeartRate;
class BreathFrequency;
class OxygenSaturation;
class BloodPressure;

class SensorSpecsVisitorInterface {
public:
    virtual void visitTemperature(Temperature&) = 0;
    virtual void visitHeartRate(HeartRate&) = 0;
    virtual void visitBreathFrequency(BreathFrequency&) = 0;
    virtual void visitOxygenSaturation() = 0;
    virtual void visitBloodPressure() = 0;
};

#endif // SENSORSPECSVISITORINTERFACE_H
