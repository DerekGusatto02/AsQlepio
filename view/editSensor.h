#ifndef EDITSENSOR_H
#define EDITSENSOR_H

#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "model/sensor.h"
#include "sensorSpecsVisitor.h"

class EditSensor : public QWidget {
    Q_OBJECT
protected:
    QLabel* title;
    QPushButton* cancel;
    QPushButton* confirm;
    QPushButton* remove;
    QPushButton* simulate;
    QHBoxLayout* buttons;
    QVBoxLayout* editSensorLayout;
    /* QWidget* form;
    QFormLayout* commonLayout; */

    QVBoxLayout* commonLayout;

    QHBoxLayout* idLayout;
    QHBoxLayout* nameLayout;
    QHBoxLayout* reliabilityLayout;
    QHBoxLayout* rangeLayout;

    QWidget* otherSpecs;
    QLabel* sensorId;
    QLabel* sensorName;
    QLabel* sensorReliability;
    QLabel* sensorRange;
    QLabel* id;
    QLineEdit* name;
    QLineEdit* reliability;
    QLineEdit* min;
    QLineEdit* max;
    void showEvent(QShowEvent *event) override;
    int _id;
    Sensor* _sensor;
    void renameEditSensor();

public:
    EditSensor(Sensor* sensor, int id = -1, QWidget* parent=0);
    void displayAttributes();
    void setSensor(Sensor* sensor);
    void requestData(Sensor* type, int id);


signals:
    void sensorDataRequested(unsigned int id);
    void removeSensor(unsigned int id);
    void backToHome();
    void startSimulation(Sensor* sensor);
    void getNewSensor(Sensor* type);
    void needToSaveSensor(Sensor* sensor);

};

#endif // EDITSENSOR_H
