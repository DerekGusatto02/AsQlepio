#include "chooseTypeDialog.h"

ChooseTypeDialog::ChooseTypeDialog() {
    //this->setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Scegli sensore");
    //setFixedSize(QSize(600, 600));

    chooseType = new QLabel("Seleziona una tipologia di sensori");
    chooseType->setAlignment(Qt::AlignCenter);

    temperature = new QRadioButton("Temperatura");
    type = new Temperature();
    temperature->setChecked(true); //default choice: avoid sending without a selection
    connect(temperature, &QRadioButton::toggled, this, &ChooseTypeDialog::handleRadioButtons);

    heartRate = new QRadioButton("Battito cardiaco");
    connect(heartRate, &QRadioButton::toggled, this, &ChooseTypeDialog::handleRadioButtons);

    oxygenSaturation = new QRadioButton("Saturazione");
    connect(oxygenSaturation, &QRadioButton::toggled, this, &ChooseTypeDialog::handleRadioButtons);

    breathFrequency = new QRadioButton("Frequenza atti respiratori");
    connect(breathFrequency, &QRadioButton::toggled, this, &ChooseTypeDialog::handleRadioButtons);

    bloodPressure = new QRadioButton("Pressione sanguigna");
    connect(bloodPressure, &QRadioButton::toggled, this, &ChooseTypeDialog::handleRadioButtons);

    next = new QPushButton("Continua");
    next->setProperty("class", "mainButton");
    next->setFixedSize(160, 30);

    connect(next, &QPushButton::clicked, this, [this](){emit newSensor(type, -1); this->close();});

    firstSensorRow = new QHBoxLayout();
    firstSensorRow->addWidget(temperature);
    firstSensorRow->addWidget(heartRate);
    firstSensorRow->addWidget(oxygenSaturation);

    secondSensorRow = new QHBoxLayout();
    secondSensorRow->addWidget(breathFrequency);
    secondSensorRow->addWidget(bloodPressure);

    layout = new QVBoxLayout();
    layout->addWidget(chooseType);
    layout->addLayout(firstSensorRow);
    layout->addLayout(secondSensorRow);
    layout->addWidget(next, 1, Qt::AlignHCenter);

    setLayout(layout);
}

void ChooseTypeDialog::handleRadioButtons() {
    if (type) delete type;
    if (temperature->isChecked()) type = new Temperature();        
    if (heartRate->isChecked()) type = new HeartRate();
    if (oxygenSaturation->isChecked()) type = new OxygenSaturation();
    if (breathFrequency->isChecked()) type = new BreathFrequency();
    if (bloodPressure->isChecked()) type = new BloodPressure();
}
