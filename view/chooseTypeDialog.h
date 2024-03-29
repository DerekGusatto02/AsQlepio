#ifndef CHOOSETYPEDIALOG_H
#define CHOOSETYPEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "../model/temperature.h"
#include "../model/heartRate.h"
#include "../model/bloodPressure.h"
#include "../model/oxygenSaturation.h"
#include "../model/breathFrequency.h"

class ChooseTypeDialog : public QDialog {
private:
    Q_OBJECT
    QLabel* chooseType;
    QRadioButton* temperature;
    QRadioButton* heartRate;
    QRadioButton* oxygenSaturation;
    QRadioButton* breathFrequency;
    QRadioButton* bloodPressure;

    QPushButton* next;

    QHBoxLayout* firstSensorRow;
    QHBoxLayout* secondSensorRow;

    QVBoxLayout* layout;

    Sensor* type;

public:
    ChooseTypeDialog();

signals:

    void newSensor(Sensor* sensor, int id=-1);

public slots:
    void handleRadioButtons();

};

#endif // CHOOSETYPEDIALOG