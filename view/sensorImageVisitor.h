#ifndef SENSORIMAGEVISITOR_H
#define SENSORIMAGEVISITOR_H

#include "../model/sensorImageVisitorInterface.h"
#include "../model/temperature.h"
#include "../model/heartRate.h"
#include "../model/bloodPressure.h"
#include "../model/oxygenSaturation.h"
#include "../model/breathFrequency.h"
#include "editSensor.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QIntValidator>

class SensorImageVisitor : public SensorImageVisitorInterface {
private:
    QLabel* image;

public:
    QLabel* getImage() const;
    virtual void visitTemperature();
    virtual void visitHeartRate();
    virtual void visitBreathFrequency();
    virtual void visitBloodPressure();
    virtual void visitOxygenSaturation();
};

#endif // SENSORIMAGEVISITOR_H
