#ifndef SENSORSPECSVISITOR_H
#define SENSORSPECSVISITOR_H

#include "../model/sensorSpecsVisitorInterface.h"
#include "../model/temperature.h"
#include "../model/heartRate.h"
#include "../model/breathFrequency.h"
#include "editSensor.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QIntValidator>

class SensorSpecsVisitor : public SensorSpecsVisitorInterface {
private:
    QVBoxLayout* layout;
  
public:
    QVBoxLayout* getLayout() const;
    virtual void visitTemperature(Temperature&);
    virtual void visitHeartRate(HeartRate&);
    virtual void visitBreathFrequency(BreathFrequency&);
    virtual void visitOxygenSaturation();
    virtual void visitBloodPressure();
};

#endif // SENSORSPECSVISITOR_H
