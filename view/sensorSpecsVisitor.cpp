#include "sensorSpecsVisitor.h"

QVBoxLayout* SensorSpecsVisitor::getLayout() const {
    return layout;
}

void SensorSpecsVisitor::visitOxygenSaturation() {
    layout = nullptr;
}

void SensorSpecsVisitor::visitBloodPressure() {
    layout = nullptr;
}

void SensorSpecsVisitor::visitTemperature(Temperature& temperature) {
    QLabel* sensorUoM = new QLabel("Unità di misura: ");
    QLabel* uoM;
    if (temperature.getUnitOfMesure()) uoM= new QLabel("Celsius");
    else uoM= new QLabel("Fahreneit");

    //QPushButton* convert = new QPushButton("Converti");

    QHBoxLayout* firstRow = new QHBoxLayout();
    firstRow->addWidget(sensorUoM);
    firstRow->addWidget(uoM);

    layout = new QVBoxLayout();
    layout->addLayout(firstRow);
    //layout->addWidget(convert);
}

void SensorSpecsVisitor::visitHeartRate(HeartRate& heartRate) {
    QLabel* sensorIsUnderStress = new QLabel("Stato: ");
    QLabel* isUnderStress;
    if(heartRate.getIsUnderStress()){
        isUnderStress = new QLabel("Sotto sforzo");
    }else{
        isUnderStress = new QLabel("A riposo");
    }

    QHBoxLayout* firstRow = new QHBoxLayout();
    firstRow->addWidget(sensorIsUnderStress);
    firstRow->addWidget(isUnderStress);

    layout = new QVBoxLayout();
    layout->addLayout(firstRow);
}

void SensorSpecsVisitor::visitBreathFrequency(BreathFrequency& breathFrequency) {
    QLabel* sensorAge = new QLabel("Età: ");

    QIntValidator* ageValidator = new QIntValidator();

    QLineEdit* age = new QLineEdit();
    age->setValidator(ageValidator);
    age->setText(QString::number(breathFrequency.getAge()));

    QHBoxLayout* firstRow = new QHBoxLayout();
    firstRow->addWidget(sensorAge);
    firstRow->addWidget(age);

    QLabel* sensorIsUnderStress = new QLabel("Stato: ");
    QLabel* isUnderStress;
    if(breathFrequency.getIsUnderStress()){
        isUnderStress = new QLabel("Sotto sforzo");
    }else{
        isUnderStress = new QLabel("A riposo");
    }

    QHBoxLayout* secondRow = new QHBoxLayout();
    secondRow->addWidget(sensorIsUnderStress);
    secondRow->addWidget(isUnderStress);

    layout = new QVBoxLayout();
    layout->addLayout(firstRow);
    layout->addLayout(secondRow);
}

