#ifndef SENSORSAVEVISITORINTERFACE_H
#define SENSORSAVEVISITORINTERFACE_H

class Temperature;
class HeartRate;
class BreathFrequency;
class OxygenSaturation;
class BloodPressure;

class SensorSaveVisitorInterface {
public:
    virtual void visitTemperature() = 0;
    virtual void visitHeartRate() = 0;
    virtual void visitBreathFrequency(BreathFrequency&) = 0;
    virtual void visitOxygenSaturation() = 0;
    virtual void visitBloodPressure() = 0;
};
#endif // SENSORSAVEVISITORINTERFACE_H
