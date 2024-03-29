#include "sensorSaveVisitor.h"

SensorSaveVisitor::SensorSaveVisitor(QVBoxLayout *layout) : layout(layout) {}

void SensorSaveVisitor::visitOxygenSaturation() {

}

void SensorSaveVisitor::visitBloodPressure() {

}

void SensorSaveVisitor::visitTemperature() {


}

void SensorSaveVisitor::visitHeartRate() {

}

void SensorSaveVisitor::visitBreathFrequency(BreathFrequency& breathFrequency) {
    QLayoutItem* item = layout->itemAt(0);
    if(item->layout()){
        QHBoxLayout* firstRow = qobject_cast<QHBoxLayout*>(item->layout());
        QLineEdit* age = qobject_cast<QLineEdit*>(firstRow->itemAt(1)->widget());
        breathFrequency.setAge(age->text().toUInt());
    }

}

