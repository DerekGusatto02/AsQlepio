#ifndef SENSORSAVEVISITOR_H
#define SENSORSAVEVISITOR_H

#include "../model/sensorSaveVisitorInterface.h"
#include "../model/temperature.h"
#include "../model/heartRate.h"
#include "../model/breathFrequency.h"
#include "editSensor.h"

class SensorSaveVisitor: public SensorSaveVisitorInterface {
private:
    QVBoxLayout* layout;
public:
    SensorSaveVisitor(QVBoxLayout* layout);
    virtual void visitTemperature();
    virtual void visitHeartRate();
    virtual void visitBreathFrequency(BreathFrequency&);
    virtual void visitOxygenSaturation();
    virtual void visitBloodPressure();
};


#endif // SENSORSAVEVISITOR_H
