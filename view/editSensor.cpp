#include "editSensor.h"
#include "model/model.h"
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>

EditSensor::EditSensor(Sensor* type, int id, QWidget* parent) : QWidget(parent) {
    title = new QLabel(QString::number(id));
    title->setProperty("class", "title");
    title->setAlignment(Qt::AlignCenter);

    cancel = new QPushButton("Indietro");
    cancel->setProperty("class", "editButton");
    cancel->setFixedSize(150, 30);
    confirm = new QPushButton("Salva");
    confirm->setProperty("class", "mainButton");
    confirm->setFixedSize(150, 30);
    remove = new QPushButton("Elimina");
    remove->setProperty("class", "cancelButton");
    remove->setFixedSize(150, 30);
    simulate = new QPushButton("Simula");
    simulate->setProperty("class", "mainButton");
    simulate->setFixedSize(150, 30);

    buttons = new QHBoxLayout();
    buttons->addWidget(cancel);
    buttons->addWidget(confirm);
    buttons->addWidget(remove);
    buttons->addWidget(simulate);
    buttons->setAlignment(Qt::AlignCenter);

    connect(cancel, &QPushButton::clicked, this, &EditSensor::backToHome);
    connect(remove, &QPushButton::clicked, this, [this](){emit removeSensor(this->_id);});
    connect(confirm, &QPushButton::clicked, this, [this](){emit needToSaveSensor(this->_sensor);});
    connect(simulate, &QPushButton::clicked, this, [this](){emit startSimulation(this->_sensor);});

    idLayout = new QHBoxLayout();
    nameLayout = new QHBoxLayout();
    reliabilityLayout = new QHBoxLayout();
    rangeLayout = new QHBoxLayout();

    commonLayout = new QVBoxLayout();
    otherSpecs = new QWidget();

    editSensorLayout = new QVBoxLayout(this);
    editSensorLayout->addStretch();
    editSensorLayout->addWidget(title);
    editSensorLayout->addLayout(buttons);
    editSensorLayout->addLayout(commonLayout);
    editSensorLayout->addWidget(otherSpecs);
    editSensorLayout->addStretch();

}

void EditSensor::requestData(Sensor* type, int id){
    if(id != -1){
        this->_id = id;
        emit sensorDataRequested(_id );
    }else{
        emit getNewSensor(type);
        _id = _sensor->getId();
        this->renameEditSensor();

    }

    displayAttributes();
}
void EditSensor::renameEditSensor(){
    title = new QLabel(QString::number(_id));
}

void EditSensor::displayAttributes(){
    sensorId = new QLabel("ID: ");
    sensorName = new QLabel("Nome: ");
    sensorReliability = new QLabel("Affidabilità: ");
    sensorRange = new QLabel("Campo di misura: ");
    id = new QLabel(QString::number(_sensor->getId()));
    name = new QLineEdit();
    name->setText(QString::fromStdString(_sensor->getName()));
    reliability = new QLineEdit();
    QIntValidator* reliabilityValidator = new QIntValidator(0, 100, this);
    reliability->setValidator(reliabilityValidator);
    reliability->setText(QString::number(_sensor->getReliability()));
    QIntValidator* numberValidator = new QIntValidator(0, 4294967295, this);
    min = new QLineEdit();
    min->setValidator(numberValidator);
    min->setText(QString::number(_sensor->getRange().getMinimum()));
    max = new QLineEdit();
    max->setValidator(numberValidator);
    max->setText(QString::number(_sensor->getRange().getMaximum()));
    QHBoxLayout* range = new QHBoxLayout();
    range->addWidget(min);
    range->addWidget(max);

    idLayout->addWidget(sensorId);
    idLayout->addWidget(id);

    nameLayout->addWidget(sensorName);
    nameLayout->addWidget(name);

    reliabilityLayout->addWidget(sensorReliability);
    reliabilityLayout->addWidget(reliability);

    rangeLayout->addWidget(sensorRange);
    rangeLayout->addLayout(range);

    commonLayout->addLayout(idLayout);
    commonLayout->addLayout(nameLayout);
    commonLayout->addLayout(reliabilityLayout);
    commonLayout->addLayout(rangeLayout);

    SensorSpecsVisitor visitor;
    _sensor->acceptSpecs(visitor);
    if (visitor.getLayout()) otherSpecs->setLayout(visitor.getLayout());
}

void EditSensor::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    emit sensorDataRequested(this->_id);
}

void EditSensor::setSensor(Sensor* sensor){
    this->_sensor = sensor;
}
