#include "loader.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QIODevice>
#include "bloodPressure.h"
#include "oxygenSaturation.h"
#include "temperature.h"
#include "heartRate.h"
#include "breathFrequency.h"

std::vector<Sensor*> SensorLoader::loadFromFile(const QString& filename) {
    std::vector<Sensor*> sensors;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        // TODO: gestisci l'errore
        return sensors;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject mainObject = doc.object();
    QJsonArray sensorArray = mainObject["sensors"].toArray();

    for (const QJsonValue& value : sensorArray) {
        QJsonObject sensorObject = value.toObject();
        QString type = sensorObject["type"].toString();
        //call the right fromJson method
        Sensor* sensor;
        if (type == "BloodPressure") {
            sensor = BloodPressure::fromJson(sensorObject);
        } else if (type == "OxygenSaturation") {
            sensor = OxygenSaturation::fromJson(sensorObject);
        }else if (type == "Temperature") {
            sensor = Temperature::fromJson(sensorObject);
        }else if(type == "HeartRate"){
            sensor = HeartRate::fromJson(sensorObject);
        }else if(type == "BreathFrequency"){
            sensor = BreathFrequency::fromJson(sensorObject);
        }    
        sensors.push_back(sensor);
    }

    return sensors;
}
