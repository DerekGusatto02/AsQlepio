#include "sensorImageVisitor.h"

QLabel* SensorImageVisitor::getImage() const {
    return image;
}

void SensorImageVisitor::visitTemperature() {
    image = new QLabel();
    image->setPixmap(QIcon(":/img/temperature.png").pixmap(30, 30));
}

void SensorImageVisitor::visitHeartRate() {
    image = new QLabel();
    image->setPixmap(QIcon(":/img/heart-rate-2.png").pixmap(30, 30));
}

void SensorImageVisitor::visitBreathFrequency() {
    image = new QLabel();
    image->setPixmap(QIcon(":/img/breath.png").pixmap(30, 30));
}

void SensorImageVisitor::visitOxygenSaturation() {
    image = new QLabel();
    image->setPixmap(QIcon(":/img/oxygen.png").pixmap(30, 30));
}

void SensorImageVisitor::visitBloodPressure() {
    image = new QLabel();
    image->setPixmap(QIcon(":/img/blood-pressure.png").pixmap(30, 30));
}
